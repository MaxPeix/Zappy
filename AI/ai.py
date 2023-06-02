from connection import Comm
import zappyAI as zp


class AI:
    _dead: bool = False
    _direction: zp.Direction = zp.Direction.N
    _comm: Comm
    _pos: zp.Pos = zp.Pos(5, 5)
    _id: int
    _worldSize: zp.Size
    _teamName: str
    _level: int = 1
    _world: list[list[zp.Tile]]
    _ticks: int = 0

    def __init__(self, comm: Comm, team_name: str):
        self._comm = comm
        self._teamName = team_name
        data: list[str] = self._comm.recv()
        if data != ["WELCOME"]:
            raise ConnectionError("Invalid response")
        self._login(team_name)
        # init world with empty tiles from world size
        self._world = [[zp.Tile(False, []) for x in range(self._worldSize.width)] for y in
                       range(self._worldSize.height)]
        if self.connect_nbr() > 1:
            pass  # TODO: ask word info on broadcast

    def draw_map(self):
        for y in range(self._worldSize.height):
            for x in range(self._worldSize.width):
                if self._pos.x == x and self._pos.y == y:
                    if self._direction == zp.Direction.N:
                        print("^", end="")
                    elif self._direction == zp.Direction.E:
                        print(">", end="")
                    elif self._direction == zp.Direction.S:
                        print("v", end="")
                    elif self._direction == zp.Direction.W:
                        print("<", end="")
                    continue
                print(self._world[y][x], end="")
            print()

    def _on_message(self, direction: zp.Direction, message: str):
        print("Message from " + str(direction) + ": " + message)

    def _recv(self) -> list[str]:
        data: list[str] = self._comm.recv()
        if "dead" in data:
            self._dead = True
        else:
            for line in data:
                if line.startswith("message "):
                    try:
                        direction: zp.Direction = zp.Direction(int(line[8:9]))
                    except ValueError:
                        raise ConnectionError("Invalid response")
                    self._on_message(direction, line[9:])
                    if len(data) == 1:
                        return self._recv()
        return data

    def _login(self, team_name: str):
        res: tuple[int, tuple[int, int]] = (0, (0, 0))
        data: list[str]

        self._comm.send(team_name + "\n")
        data = self._recv()
        if len(data) != 2:
            raise ConnectionError("Invalid response")
        try:
            res = (int(data[0]),
                   (int(data[1].split(" ")[0]), int(data[1].split(" ")[1])))
        except ValueError:
            raise ConnectionError("Invalid response")
        self._id = res[0]
        self._worldSize = zp.Size(res[1][0], res[1][1])

    def _get_objects(self, data: str) -> list[list[zp.Object] | None]:
        objects: list[list[zp.Object] | None] = []
        if not data.startswith("[") or not data.endswith("]"):
            raise ValueError("Invalid message: " + data)
        tmp: list[str | None] = data[2:-2].split(",")
        for i in range(len(tmp)):
            if tmp[i] == "None":
                tmp[i] = None
                continue
            tmp[i] = tmp[i].strip()
        for objs in tmp:
            if objs is None:
                objects.append(None)
                continue
            current: list[zp.Object] = []
            for obj in objs.split(" "):
                if obj == "":
                    continue
                current.append(zp.get_object(obj))
            objects.append(current)
        return objects

    def forward(self):
        self._comm.send("Forward\n")
        if self._recv() != ["ok"]:
            raise ConnectionError("Invalid response")
        if self._direction == zp.Direction.N:
            self._pos.y -= 1
        elif self._direction == zp.Direction.E:
            self._pos.x += 1
        elif self._direction == zp.Direction.S:
            self._pos.y += 1
        elif self._direction == zp.Direction.W:
            self._pos.x -= 1
        else:
            raise ValueError("Invalid direction")
        self._ticks += 7

    def right(self):
        self._comm.send("Right\n")
        self._ticks += 7
        if self._recv() != ["ok"]:
            raise ConnectionError("Invalid response")
        self._direction = zp.Direction(
            (self._direction.value + (1 if self._direction.value % 2 == 0 else 2) if self._direction.value < 6 else 1))

    def left(self):
        self._comm.send("Left\n")
        self._ticks += 7
        if self._recv() != ["ok"]:
            raise ConnectionError("Invalid response")
        self._direction = zp.Direction(
            (self._direction.value - (1 if self._direction.value % 2 == 0 else 2) if self._direction.value > 2 else 7))

    def _at(self, relative_pos: tuple[int, int]) -> tuple[int, int]:
        y, x = relative_pos
        if self._direction == zp.Direction.S:
            return self._pos.y + y, self._pos.x + x
        elif self._direction == zp.Direction.E:
            return self._pos.y - x, self._pos.x + y
        elif self._direction == zp.Direction.N:
            return self._pos.y - y, self._pos.x - x
        elif self._direction == zp.Direction.W:
            return self._pos.y - x, self._pos.x - y
        else:
            raise ValueError("Invalid direction")

    def look(self):
        nb_tiles: list[int] = [1, 3, 15, 24, 45, 72, 108, 162, 225, 324, 521]
        self._comm.send("Look\n")
        self._ticks += 7
        data: list[str] = self._recv()
        res: list[list[zp.Object] | None] = self._get_objects(data[0])
        if len(res) - 1 != nb_tiles[self._level]:
            raise ConnectionError("Invalid response")
        for lv in range(self._level + 1):
            for i in range(-lv, nb_tiles[lv] - lv):
                pos = self._at((lv, i))
                self._world[pos[0]][pos[1]] = zp.Tile(True, res.pop(0))

    def inventory(self) -> list[zp.Object]:
        res: list[zp.Object] = []
        self._comm.send("Inventory\n")
        return res

    def broadcast(self, message: str):
        self._comm.send("Broadcast " + message + "\n")
        self._ticks += 7

    def connect_nbr(self) -> int:
        nb_connect: int = 0
        data: list[str]
        self._comm.send("Connect_nbr\n")
        data = self._comm.recv()
        if len(data) != 1:
            raise ConnectionError("Invalid response")
        nb_connect = int(data[0])
        return nb_connect

    def fork(self):
        self._comm.send("Fork\n")
        self._ticks += 42
        if self._recv() != ["ok"]:
            raise ConnectionError("Invalid response")

    def eject(self):
        self._comm.send("Eject\n")
        self._ticks += 7
        if self._recv() != ["ok"]:
            raise ConnectionError("Invalid response")

    def take(self, resource: zp.objects) -> bool:
        self._comm.send("Take " + resource.name + "\n")
        res: list[str] = self._recv()
        if res == ["ok"]:
            return True
        elif res == ["ko"]:
            return False
        raise ConnectionError("Invalid response")

    def set(self, resource: zp.objects):
        self._comm.send("Set " + resource.name + "\n")

    def incantation(self):
        self._comm.send("Incantation\n")
        self._ticks += 300
