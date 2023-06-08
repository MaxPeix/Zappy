import logging
import utils
from ai import AI
import zappyAI as zp


class Brain:
    _ai: AI
    _lost: bool = True

    def __init__(self, team_name: str, ip: str, port: int, log_level: int = logging.INFO) -> None:
        self._ai = AI(utils.Comm(ip, port, log_level=log_level), team_name)

    def on_tile(self) -> None:
        self._ai.draw_map()
        print("pos:", self._ai.pos)

    def forward(self) -> None:
        self._ai.forward()
        self.on_tile()

    def turn(self, direction: zp.Direction) -> None:
        while self._ai.direction != direction:
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
            if self._ai.pos.y < pos.y:
                self.down()
            elif self._ai.pos.y > pos.y:
                self.up()
            if look:
                self._ai.look()

    def _cartography_next_column(self, start: zp.Pos, end: zp.Pos, up: bool) -> None:
        for i in range(self._ai.level + 1):
            self.right()
        # if up:
        #     self.down()
        # else:
        #     self.up()
        self._cartography_next_tile(start, end, not up)

    def _cartography_next_tile(self, start: zp.Pos, end: zp.Pos, up: bool) -> None:
        if up:
            self.turn(zp.Direction.N)
        else:
            self.turn(zp.Direction.S)
        self._ai.look()
        for i in range(self._ai.level):
            if up:
                self.up()
            else:
                self.down()
        if self._ai.pos.x >= end.x and self._ai.pos.y <= end.y:
            return
        if up:
            if self._ai.pos.y <= end.y:
                return self._cartography_next_column(start, end, up)
        else:
            if self._ai.pos.y >= start.y:
                return self._cartography_next_column(start, end, up)
        if up:
            self.up()
        else:
            self.down()
        self._cartography_next_tile(start, end, up)

    def cartography(self, start: zp.Pos, end: zp.Pos) -> None:
        if start.x > end.x:
            start.x, end.x = end.x, start.x
        if start.y < end.y:
            start.y, end.y = end.y, start.y
        self.goto(start)
        self.turn(zp.Direction.N)
        self._cartography_next_tile(start, end, True)

    def run(self) -> None:
        pass
