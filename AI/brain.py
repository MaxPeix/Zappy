import logging
import zappyAI as zp
import ai as zp_ai
import utils
import os
from typing import Callable
from dataclasses import dataclass
import json


class Brain:
    ai: zp_ai.AI
    _look_for: zp.Resources = zp.Resources(0, 0, 0, 0, 0, 0, 0, 0)
    _status: zp.Status = zp.Status.NOTHING
    _prev_status: zp.Status = zp.Status.NOTHING
    _cartography_last_pos: zp.Pos = zp.Pos(0, 0)
    food_wanted: int = zp_ai.FOOD_WANTED
    master_direction: zp.Direction = zp.Direction.N

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
            while self.ai.inventory[zp.ObjectType.FOOD] < self.food_wanted and \
                    self.ai.world[self.ai.pos].objects[zp.ObjectType.FOOD] > 0:
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
        # input("press enter to continue")
        self._action(zp.Evt.ON_TILE)
        self.ai.draw_map()
        print("pos:", self.ai.pos)

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
            print("direction:", self.ai.direction, "wanted:", direction)
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
            print("already on resource")
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
        print("ops: ", ops)
        while ops[1] > 0:
            print("##############################################################################################")
            print("ops: ", ops)
            print("##############################################################################################")
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
            self.ai.recv("new master")
        print("master found")
        while not self.ai.master_found:
            self.find_master()

    def find_master(self) -> None:
        self.ai.recv("ping master")
        if self.master_direction == zp.Direction.TOP:
            self.forward()
            self.ai.broadcast(self.ai.msg_handler["orientation master"].to_json(False, self.ai.master_id))
            self.ai.recv("orientation master")
            self.ai.recv("ping master")
            self.turn(self.master_direction)
            self.forward()
            self.turn(zp.Direction.N)
            self.ai._pos = zp.Pos(5, 5)
            while True:
                pass

        self.turn(self.master_direction)
        self.forward()

    def run(self) -> None:
        # TODO: check if map already cartography
        # TODO: check if master
        # TODO: check if lonely

        print("jfkldsjfklmsqdjflmdsjfimlqdsjmlkzgmreraegjmlergjklmfemfqdskufhdsjkfjdklnfqskjhflskqj")

        if self.ai.role == zp.Role.WORKER:
            self.worker()
            return
        print("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
        while True:
            self.ai.broadcast(self.ai.msg_handler["ping master"].to_json(False))
            self.take(zp.ObjectType.FOOD)

        # self.cartography(zp.Pos(0, 0), zp.Pos(self.ai.world.size.height - 1, self.ai.world.size.width - 1))
        # for resource in ai.OBJECTIVES[self.ai.level - 1]:
        #     if resource == zp.ObjectType.PLAYER:
        #         continue
        #     while self.ai.inventory[resource] < ai.OBJECTIVES[self.ai.level - 1][resource]:
        #         if not self.go_where(resource, True, 10):
        #             raise ValueError("can't find resource")
        #         self.take(resource)
        # self.on_look()
        # print(self.ai.inventory)
        # self.ai.set(zp.ObjectType.LINEMATE)
        # try:
        #     self.ai.incantation(False)
        # except ValueError as e:
        #     print("incantation failed: ", e)
        #     self.on_look()
        # pass


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
            "from": os.getpid(),
            "to": to,
            "ans": ans,
            "what": self._name,
            "data": data
        }
        return json.dumps(res)

    def __call__(self, direction: zp.Direction, msg: dict) -> None:
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
                msg.brain.ai.master_id = os.getpid()
                msg.brain.ai.broadcast(msg["new master"].to_json(True))
    else:
        if msg.brain.ai.role == zp.Role.MASTER:
            msg.brain.ai.broadcast(msg["bootstrap master"].to_json(True, int(data["from"])))
        else:
            msg.brain.ai.broadcast(msg["bootstrap master"].to_json(True, int(data["from"])))


def send_bootstrap_master(msg: Message, *args, **kwargs) -> str | None:
    if msg.brain.ai.role == zp.Role.MASTER:
        return str(os.getpid())
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
        return str(os.getpid())


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
        new_direction: zp.Direction = zp.Direction(int(data["data"]))
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
    elif msg.brain.ai.role == zp.Role.MASTER:
        msg.brain.ai.broadcast(msg["orientation master"].to_json(True, int(data["from"]), direction=direction))


def send_orientation_master(msg: Message, *args, **kwargs) -> str | None:
    if msg.brain.ai.role == zp.Role.MASTER:
        if "direction" in kwargs:
            return str(int(kwargs["direction"].value))
    else:
        return "?"
