import logging

import ai
import zappyAI as zp
import ai as zp_ai
import utils
from typing import Callable
from dataclasses import dataclass
import json
import time


class Brain:
    ai: zp_ai.AI
    _look_for: zp.Resources = zp.Resources(0, 0, 0, 0, 0, 0, 0, 0)
    _status: zp.Status = zp.Status.NOTHING
    _prev_status: zp.Status = zp.Status.NOTHING
    _cartography_last_pos: zp.Pos = zp.Pos(0, 0)
    food_wanted: int = zp_ai.FOOD_WANTED
    master_direction: zp.Direction = zp.Direction.N
    players: list[int] = []

    def __init__(self, team_name: str, ip: str, port: int, log_level: int = logging.INFO) -> None:
        self.ai = zp_ai.AI(utils.Comm(ip, port, log_level=log_level), team_name)
        self.ai.add_message(Message(self))
        self.ai.start()
        self.change_status(zp.Status.SEARCHING)

    def change_status(self, status: zp.Status) -> None:
        self._prev_status = self._status
        self._status = status
        if status == zp.Status.DYING:
            print(utils.RED, end="")
        elif status == zp.Status.SEARCHING:
            print(utils.GREEN, end="")
        elif status == zp.Status.MOVING:
            print(utils.YELLOW, end="")
        elif status == zp.Status.NOTHING:
            print(utils.WHITE, end="")

    def _action(self, evt: zp.Evt) -> None:
        if self.ai.world[self.ai.pos].known:
            if self.ai.id in [1, 2, 3, 4] and self.ai.pos == zp.Pos(5, 5):
                pass
            else:
                while self.ai.world[self.ai.pos].objects[zp.ObjectType.FOOD] > 0:
                    self.take(zp.ObjectType.FOOD)
        if self.ai.inventory[zp.ObjectType.FOOD] < 3:
            self.change_status(zp.Status.DYING)
        if self._status == zp.Status.DYING:
            self.dying(evt)
        elif self._status == zp.Status.SEARCHING:
            self.searching(evt)
        elif self._status == zp.Status.MOVING:
            self.moving(evt)

    def on_tile(self) -> None:
        self._action(zp.Evt.ON_TILE)
        self.ai.draw_map()

    def on_look(self) -> None:
        self.ai.look()
        self._action(zp.Evt.ON_LOOK)
        self.ai.draw_map()

    def on_turn(self) -> None:
        self.ai.draw_map()

    def dying(self, evt: zp.Evt, go_back: bool = True) -> None:
        if self.ai.inventory.food < 10:
            prev_pos = self.ai.pos
            prev_dir = self.ai.direction
            self.go_where(zp.ObjectType.FOOD, True)
            self.take(zp.ObjectType.FOOD)
            self.dying(evt, False)
            if go_back:
                self.goto(prev_pos)
                self.turn(prev_dir)
        else:
            self.change_status(self._prev_status)

    def _searching(self, evt: zp.Evt, lvl: int) -> None:
        for resource in zp_ai.OBJECTIVES[lvl - 1]:
            if resource == zp.ObjectType.PLAYER:
                continue
            while self.ai.inventory[resource] < zp_ai.OBJECTIVES[lvl - 1][resource] and \
                    self.ai.world[self.ai.pos].objects[resource] > 0:
                self.take(resource)

    def searching(self, evt: zp.Evt) -> None:
        if not self.ai.world[self.ai.pos].known:
            return
        self._searching(evt, self.ai.level)
        self._searching(evt, self.ai.level + 1)

    def moving(self, evt: zp.Evt) -> None:
        pass

    def take(self, resource: zp.ObjectType) -> bool:
        if not self.ai.take(resource):
            self.ai.look()
            return self.ai.take(resource)
        return True

    def forward(self) -> None:
        self.ai.forward()
        self.on_tile()

    def turn(self, direction: zp.Direction) -> None:
        if direction.value % 2 == 0:
            raise ValueError("direction must be odd")
        while self.ai.direction != direction:
            self.on_turn()
            if self.ai.direction < direction:
                self.ai.left()
            else:
                self.ai.right()

    def up(self) -> None:
        self.turn(zp.Direction.N)
        self.forward()

    def down(self) -> None:
        self.turn(zp.Direction.S)
        self.forward()

    def left(self) -> None:
        self.turn(zp.Direction.W)
        self.forward()

    def right(self) -> None:
        self.turn(zp.Direction.E)
        self.forward()

    def goto(self, pos: zp.Pos, look: bool = False) -> None:
        while self.ai.pos != pos:
            if self.ai.pos.x < pos.x:
                self.right()
            elif self.ai.pos.x > pos.x:
                self.left()
            elif self.ai.pos.y < pos.y:
                self.down()
            elif self.ai.pos.y > pos.y:
                self.up()
            if look:
                self.on_look()

    def go_where(self, resource: zp.ObjectType, look: bool = False, recursion: int | None = None) -> bool:
        if self.ai.world[self.ai.pos].objects[resource] > 0:
            return True
        i: int = 1
        x: int = self.ai.pos.x
        y: int = self.ai.pos.y
        if self.ai.world.size.width > self.ai.world.size.height:
            size: int = self.ai.world.size.width
        else:
            size: int = self.ai.world.size.height
        for _ in range((size // 2) + 1):
            x += i
            if self.ai.world[(y, x)].objects[resource] > 0:
                self.goto(zp.Pos(y, x), look)
                return True
            y -= i
            if self.ai.world[(y, x)].objects[resource] > 0:
                self.goto(zp.Pos(y, x), look)
                return True
            i += 1
            x -= i
            if self.ai.world[(y, x)].objects[resource] > 0:
                self.goto(zp.Pos(y, x), look)
                return True
            y += i
            if self.ai.world[(y, x)].objects[resource] > 0:
                self.goto(zp.Pos(y, x), look)
                return True
            i += 1
        if look and recursion is not None and recursion > 0:
            self.forward()
            self.on_look()
            return self.go_where(resource, look, recursion - 1)
        return False

    def _cartography_get_move(self, start: zp.Pos, end: zp.Pos) -> list[int, int, int]:
        zone_height: int = start.y - end.y
        zone_width: int = end.x - start.x
        triangle_height: int = self.ai.level + 1

        nb_triangle_height: int = zone_height // triangle_height
        nb_triangle_width: int = zone_width // self.ai.level

        nb_up: int = (nb_triangle_width // 2) - 1
        nb_down: int = nb_up
        if nb_triangle_width % 2 == 1:
            nb_up += 1
        return [nb_triangle_height, nb_up, nb_down]

    def _cartography_next_column(self) -> None:
        for _ in range(self.ai.level + 1):
            self.right()

    def _cartography_up_column(self, ops: list[int, int, int]) -> None:
        self.turn(zp.Direction.N)
        self.on_look()
        for idx in range(ops[0]):
            for _ in range(self.ai.level + 1):
                self.up()
            self.on_look()
            if idx == ops[0] - 1:
                self.up()

    def _cartography_down_column(self, ops: list[int, int, int]) -> None:
        self.turn(zp.Direction.S)
        self.on_look()
        for idx in range(ops[0]):
            for _ in range(self.ai.level + 1):
                self.down()
            self.on_look()
            if idx == ops[0] - 1:
                self.down()

    def cartography(self, start: zp.Pos, end: zp.Pos) -> None:
        if start == end:
            self.on_look()
            return
        if start.x > end.x:
            start.x, end.x = end.x, start.x
        if start.y < end.y:
            start.y, end.y = end.y, start.y
        if start.x < 0 or start.y < 0 or end.x > self.ai.world.size.width - 1 or end.y > self.ai.world.size.height - 1:
            raise ValueError("start and end must be inside the map")

        print("cartography from", start, "to", end)
        self.goto(start)
        self.turn(zp.Direction.N)

        ops: list[int, int, int] = self._cartography_get_move(start, end)
        while ops[1] > 0:
            self._cartography_up_column(ops)
            ops[1] -= 1
            if ops[2] > 0:
                self._cartography_next_column()
                self._cartography_down_column(ops)
                ops[2] -= 1
                if ops[1] > 0:
                    self._cartography_next_column()
        print("cartography done")

    def worker(self) -> None:
        print("worker")
        while self.ai.master_id is None:
            self.ai.recv(False)
            self.ai.exec_buffer()
        print("master found")
        while not self.ai.master_found:
            self.find_master()
        if self.ai.id == 1:
            zone: tuple[zp.Pos, zp.Pos] = (
                zp.Pos(0, 0), zp.Pos((self.ai.world.size.height - 1) // 2, (self.ai.world.size.width - 1) // 2))
        elif self.ai.id == 2:
            zone: tuple[zp.Pos, zp.Pos] = (
                zp.Pos(0, (self.ai.world.size.width - 1) // 2), zp.Pos((self.ai.world.size.height - 1) // 2,
                                                                       self.ai.world.size.width - 1))
        elif self.ai.id == 3:
            zone: tuple[zp.Pos, zp.Pos] = (
                zp.Pos((self.ai.world.size.height - 1) // 2, 0), zp.Pos(self.ai.world.size.height - 1,
                                                                        (self.ai.world.size.width - 1) // 2))
        elif self.ai.id == 4:
            zone: tuple[zp.Pos, zp.Pos] = (
                zp.Pos((self.ai.world.size.height - 1) // 2, (self.ai.world.size.width - 1) // 2),
                zp.Pos(self.ai.world.size.height - 1, self.ai.world.size.width - 1))
        else:
            print("error: id not found")
            exit(0)
        self.drop_all()
        self.cartography(zone[0], zone[1])
        self.goto(zp.Pos(5, 5))
        self.drop_all()
        self.ai.look()
        if self.ai.world[self.ai.pos].objects[zp.ObjectType.LINEMATE] < ai.OBJECTIVES[self.ai.level][
            zp.ObjectType.LINEMATE]:
            self.go_where(zp.ObjectType.LINEMATE, True)
            self.goto(zp.Pos(5, 5))
            self.ai.set(zp.ObjectType.LINEMATE)
        while True:
            self.ai.recv()

    def find_master(self) -> None:
        while not self.ai.run_message("ping master", self.ai.master_id):
            self.ai.recv(False)
        if self.master_direction == zp.Direction.TOP:
            self.forward()
            self.ai.broadcast(self.ai.msg_handler["orientation master"].to_json(False, self.ai.master_id))
            while not self.ai.run_message("orientation master", self.ai.master_id):
                self.ai.recv(False)
            while not self.ai.run_message("ping master", self.ai.master_id):
                self.ai.recv(False)
            self.turn(self.master_direction)
            self.forward()
            self.turn(zp.Direction.N)
            self.ai._pos = zp.Pos(5, 5)
            self.ai.master_found = True
            if self.ai.id > 4:
                self.ai.check_inventory()
                self.drop_all(False)
                exit(0)
                # while True:
                #     try:
                #         self.ai.check_inventory()
                #     except TimeoutError:
                #         print("Successfully died !")
                #         exit(0)
            if self.ai.id == 0:
                self.queen()

            return

        self.turn(self.master_direction)
        self.forward()

    def drop_all(self, survive: bool = True) -> None:
        for resource in self.ai.inventory:
            for _ in range(self.ai.inventory[resource]):
                if resource == zp.ObjectType.FOOD and self.ai.inventory.food <= self.food_wanted and survive:
                    continue
                self.ai.set(resource)

    def can_elevate(self) -> bool:
        self.ai.look()
        print("world:", self.ai.world[self.ai.pos].objects)
        print("level:", ai.OBJECTIVES[self.ai.level])

        for resource in self.ai.world[self.ai.pos].objects:
            if resource == zp.ObjectType.PLAYER:
                continue
            if self.ai.world[self.ai.pos].objects[resource] < ai.OBJECTIVES[self.ai.level][resource]:
                return False
        return True

    def queen_elevate(self) -> None:
        self.ai.broadcast(self.ai.msg_handler["elevate"].to_json(False))
        self.ai.look()
        while self.ai.world[self.ai.pos].objects[zp.ObjectType.PLAYER] < 6:
            self.ai.look()
        self.ai.incantation(False)

    def queen(self) -> None:
        print("queen")
        self.ai.food_wanted = 4
        while True:
            print(utils.YELLOW)
            self.ai.check_inventory()
            if self.can_elevate():
                self.queen_elevate()
            # if self.ai.connect_nbr() == 0:
            #     self.ai.fork()
            while self.ai.inventory.food < self.food_wanted:
                self.take(zp.ObjectType.FOOD)

    def run(self) -> None:
        # TODO: check if map already cartography
        # TODO: check if master
        # TODO: check if lonely

        if self.ai.role == zp.Role.WORKER:
            self.worker()
            return
        while True:
            print(utils.WHITE)
            self.ai.broadcast(self.ai.msg_handler["ping master"].to_json(False))
            if self.ai.inventory.food > self.food_wanted:
                self.ai.check_inventory()
                continue
            self.take(zp.ObjectType.FOOD)


@dataclass
class HANDLER:
    _name: str
    _recv: Callable
    _send: Callable
    _msg: 'Message'

    def to_json(self, ans: bool = False, to: int | None = None, *args, **kwargs) -> str | None:
        data: str | None = self._send(self._msg, *args, **kwargs)
        if data is None:
            return None
        if data == "null":
            data = None
        res: dict = {
            "from": self._msg.brain.ai.id,
            "to": to,
            "ans": ans,
            "what": self._name,
            "data": data
        }
        return json.dumps(res)

    def __call__(self, direction: zp.Direction, msg: dict) -> None:
        data = msg["data"]
        try:
            data = json.loads(data)
            msg["data"] = data
        except json.JSONDecodeError:
            pass
        return self._recv(self._msg, direction, msg)

    def __init__(self, msg: 'Message', name: str, recv_handler: Callable, send_handler: Callable):
        self._name = name
        self._msg = msg
        self._recv = recv_handler
        self._send = send_handler


class Message:
    HANDLERS: dict[str, HANDLER] = {}
    brain: Brain

    def __init__(self, br: Brain):
        self.brain = br

        self["bootstrap master"] = (recv_bootstrap_master, send_bootstrap_master)
        self["new master"] = (recv_new_master, send_new_master)
        self["ping master"] = (recv_ping_master, send_ping_master)
        self["orientation master"] = (recv_orientation_master, send_orientation_master)
        self["elevate"] = (recv_elevate, send_elevate)

    def __getitem__(self, item):
        return self.HANDLERS[item]

    def __setitem__(self, key, value: tuple[Callable, Callable]):
        self.HANDLERS[key] = HANDLER(self, key, value[0], value[1])


def recv_bootstrap_master(msg: Message, direction: zp.Direction, data: dict) -> None:
    if msg.brain.ai.role == zp.Role.WORKER and msg.brain.ai.master_id is not None:
        return
    if data["ans"]:
        if msg.brain.ai.role is None:
            if data["data"] == "no master":  # FIXME: doesn't work
                msg.brain.ai.role = zp.Role.MASTER
                msg.brain.ai.master_id = msg.brain.ai.id
                msg.brain.ai.broadcast(msg["new master"].to_json(True))
    else:
        if msg.brain.ai.role == zp.Role.MASTER:
            msg.brain.ai.broadcast(msg["bootstrap master"].to_json(True, int(data["from"])))
        else:
            msg.brain.ai.broadcast(msg["bootstrap master"].to_json(True, int(data["from"])))


def send_bootstrap_master(msg: Message, *args, **kwargs) -> str | None:
    if msg.brain.ai.role == zp.Role.MASTER:
        return str(msg.brain.ai.id)
    if msg.brain.ai.master_id is None:
        return "no master"
    # return str(msg.brain.ai.master_id)


def recv_new_master(msg: Message, direction: zp.Direction, data: dict) -> None:
    if not data["ans"]:
        return
    if msg.brain.ai.role == zp.Role.MASTER:
        raise ValueError("already master")
    msg.brain.ai.role = zp.Role.WORKER
    msg.brain.ai.master_id = int(data["data"])


def send_new_master(msg: Message, *args, **kwargs) -> str | None:
    if msg.brain.ai.role == zp.Role.MASTER:
        return str(msg.brain.ai.id)


def recv_ping_master(msg: Message, direction: zp.Direction, data: dict) -> None:
    if direction == zp.Direction.TOP:
        msg.brain.master_direction = zp.Direction.TOP
        return
    path: int = (direction.value if direction.value % 2 != 0 else direction.value + 1)
    if msg.brain.ai.direction == zp.Direction.N:
        pass
    elif msg.brain.ai.direction == zp.Direction.W:
        path += 2
    elif msg.brain.ai.direction == zp.Direction.S:
        path += 4
    elif msg.brain.ai.direction == zp.Direction.E:
        path += 6
    while path > 8:
        path -= 8
    msg.brain.master_direction = zp.Direction(path)


def send_ping_master(msg: Message, *args, **kwargs) -> str | None:
    return "ping"


def recv_orientation_master(msg: Message, direction: zp.Direction, data: dict) -> None:
    if data["ans"] and msg.brain.ai.role == zp.Role.WORKER:
        new_direction: zp.Direction = zp.Direction(int(data["data"]["direction"]))
        if new_direction == zp.Direction.N:
            pass
        elif new_direction == zp.Direction.W:
            msg.brain.ai.right()
        elif new_direction == zp.Direction.S:
            msg.brain.ai.right()
            msg.brain.ai.right()
        elif new_direction == zp.Direction.E:
            msg.brain.ai.left()
        msg.brain.ai._direction = zp.Direction.N
        msg.brain.ai.id = int(data["data"]["id"])
        print("new id:", msg.brain.ai.id)
    elif msg.brain.ai.role == zp.Role.MASTER:
        msg.brain.ai.broadcast(msg["orientation master"].to_json(True, int(data["from"]), direction=direction))


def send_orientation_master(msg: Message, *args, **kwargs) -> str | None:
    if msg.brain.ai.role == zp.Role.MASTER:
        if "direction" in kwargs:
            msg.brain.players.append(len(msg.brain.players))
            return json.dumps({
                "direction": str(int(kwargs["direction"].value)),
                "id": msg.brain.players[-1]
            })
    else:
        return "?"


def recv_elevate(msg: Message, direction: zp.Direction, data: dict) -> None:
    if msg.brain.ai.id == 0 or msg.brain.ai.role == zp.Role.MASTER or data["ans"]:
        return
    current_lvl = msg.brain.ai.level
    msg.brain.goto(zp.Pos(5, 5), True)
    while msg.brain.ai.level == current_lvl:
        msg.brain.ai.check_inventory()
        if msg.brain.ai.inventory.food < 3:
            if not msg.brain.ai.take(zp.ObjectType.FOOD):
                msg.brain.go_where(zp.ObjectType.FOOD)
                msg.brain.goto(zp.Pos(5, 5))


def send_elevate(msg: Message, *args, **kwargs) -> str | None:
    return "ready"
