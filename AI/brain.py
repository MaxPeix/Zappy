import logging

import ai
import utils
from ai import AI
import zappyAI as zp


class Brain:
    _ai: AI
    _look_for: zp.Resources = zp.Resources(0, 0, 0, 0, 0, 0, 0, 0)
    _status: zp.Status = zp.Status.NOTHING
    _prev_status: zp.Status = zp.Status.NOTHING
    _cartography_last_pos: zp.Pos = zp.Pos(0, 0)

    def __init__(self, team_name: str, ip: str, port: int, log_level: int = logging.INFO) -> None:
        self._ai = AI(utils.Comm(ip, port, log_level=log_level), team_name)
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
        if self._ai.world[self._ai.pos].known:
            while self._ai.inventory[zp.ObjectType.FOOD] < ai.FOOD_WANTED and \
                    self._ai.world[self._ai.pos].objects[zp.ObjectType.FOOD] > 0:
                self.take(zp.ObjectType.FOOD)
        if self._status == zp.Status.DYING:
            self.dying(evt)
        elif self._status == zp.Status.SEARCHING:
            self.searching(evt)
        elif self._status == zp.Status.MOVING:
            self.moving(evt)

    def on_tile(self) -> None:
        # input("press enter to continue")
        if self._ai.inventory.food < 3:
            self.change_status(zp.Status.DYING)
        self._action(zp.Evt.ON_TILE)
        self._ai.draw_map()
        print("pos:", self._ai.pos)

    def on_look(self) -> None:
        self._ai.look()
        self._action(zp.Evt.ON_LOOK)
        self._ai.draw_map()

    def on_turn(self) -> None:
        self._ai.draw_map()

    def dying(self, evt: zp.Evt) -> None:
        if self._ai.inventory.food < 10:
            self.go_where(zp.ObjectType.FOOD, True)
            self.take(zp.ObjectType.FOOD)
        else:
            self.change_status(self._prev_status)

    def searching(self, evt: zp.Evt) -> None:  # FIXME: find a looking algorithm
        if not self._ai.world[self._ai.pos].known:
            return
        for resource in ai.OBJECTIVES[self._ai.level - 1]:
            if resource == zp.ObjectType.PLAYER:
                continue
            while self._ai.inventory[resource] < ai.OBJECTIVES[self._ai.level - 1][resource] and \
                    self._ai.world[self._ai.pos].objects[resource] > 0:
                self.take(resource)
        pass

    def moving(self, evt: zp.Evt) -> None:
        pass

    def take(self, resource: zp.ObjectType) -> bool:
        if not self._ai.take(resource):
            self._ai.look()
            return self._ai.take(resource)
        return True

    def forward(self) -> None:
        self._ai.forward()
        self.on_tile()

    def turn(self, direction: zp.Direction) -> None:
        while self._ai.direction != direction:
            self.on_turn()
            if self._ai.direction < direction:
                self._ai.right()
            else:
                self._ai.left()

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
        while self._ai.pos != pos:
            if self._ai.pos.x < pos.x:
                self.right()
            elif self._ai.pos.x > pos.x:
                self.left()
            elif self._ai.pos.y < pos.y:
                self.down()
            elif self._ai.pos.y > pos.y:
                self.up()
            if look:
                self.on_look()

    def go_where(self, resource: zp.ObjectType, look: bool = False, recursion: int | None = None) -> bool:
        # TODO: find closest resource
        if self._ai.world[self._ai.pos].objects[resource] > 0:
            print("already on resource")
            return True
        for y in range(self._ai.world.size.height):
            for x in range(self._ai.world.size.width):
                if self._ai.world[(y, x)].objects[resource] > 0:
                    self.goto(zp.Pos(y, x), look)
                    return True
        if look and recursion is not None and recursion > 0:
            self.forward()
            self.on_look()
            return self.go_where(resource, look, recursion - 1)
        return False

    # def _cartography_next_column(self, start: zp.Pos, end: zp.Pos, up: bool) -> None:
    #     for i in range(self._ai.level + 1):
    #         if self._ai.pos.x >= end.x and self._ai.pos.y <= end.y:
    #             return
    #         self.right()
    #     # if up:
    #     #     self.down()
    #     # else:
    #     #     self.up()
    #     self._cartography_next_tile(start, end, not up)
    #
    # def _cartography_need_to_turn(self, start: zp.Pos, end: zp.Pos, up: bool) -> bool:
    #     if up:
    #         if self._ai.pos.y - (self._ai.level + 1) < end.y:
    #             return True
    #     else:
    #         if self._ai.pos.y + (self._ai.level + 1) > start.y:
    #             return True
    #     return False
    #
    # def _cartography_next_tile(self, start: zp.Pos, end: zp.Pos, up: bool) -> None:
    #     turn_next: bool = self._cartography_need_to_turn(start, end, up)
    #     if up:
    #         self.turn(zp.Direction.N)
    #     else:
    #         self.turn(zp.Direction.S)
    #     self.on_look()
    #     for i in range(self._ai.level):
    #         if up:
    #             self.up()
    #         else:
    #             self.down()
    #         if self._ai.pos.x >= end.x and self._ai.pos.y <= end.y:
    #             return
    #     if turn_next:
    #         return self._cartography_next_column(start, end, up)
    #     if up:
    #         self.up()
    #     else:
    #         self.down()
    #     self._cartography_next_tile(start, end, up)

    def _cartography_get_move(self, start: zp.Pos, end: zp.Pos) -> list[int, int, int]:
        zone_height: int = start.y - end.y
        zone_width: int = end.x - start.x
        triangle_height: int = self._ai.level + 1

        nb_triangle_height: int = zone_height // triangle_height
        nb_triangle_width: int = zone_width // self._ai.level

        nb_up: int = (nb_triangle_width // 2) - 1
        nb_down: int = nb_up
        if nb_triangle_width % 2 == 1:
            nb_up += 1
        return [nb_triangle_height, nb_up, nb_down]

    def _cartography_next_column(self) -> None:
        for _ in range(self._ai.level + 1):
            self.right()

    def _cartography_up_column(self, ops: list[int, int, int]) -> None:
        self.turn(zp.Direction.N)
        self.on_look()
        for idx in range(ops[0]):
            for _ in range(self._ai.level + 1):
                self.up()
            self.on_look()
            if idx == ops[0] - 1:
                self.up()

    def _cartography_down_column(self, ops: list[int, int, int]) -> None:
        self.turn(zp.Direction.S)
        self.on_look()
        for idx in range(ops[0]):
            for _ in range(self._ai.level + 1):
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
        if start.x < 0 or start.y < 0 or end.x > self._ai.world.size.width - 1 or end.y > self._ai.world.size.height - 1:
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

    def run(self) -> None:
        # TODO: check if map already cartografy
        # TODO: check if master
        # TODO: check if lonely

        self.cartography(zp.Pos(0, 0), zp.Pos(self._ai.world.size.height - 1, self._ai.world.size.width - 1))
        for resource in ai.OBJECTIVES[self._ai.level - 1]:
            if resource == zp.ObjectType.PLAYER:
                continue
            while self._ai.inventory[resource] < ai.OBJECTIVES[self._ai.level - 1][resource]:
                if not self.go_where(resource, True, 10):
                    raise ValueError("can't find resource")
                self.take(resource)
        self.on_look()
        print(self._ai.inventory)
        self._ai.set(zp.ObjectType.LINEMATE)
        try:
            self._ai.incantation(False)
        except ValueError as e:
            print("incantation failed: ", e)
            self.on_look()
        # pass
