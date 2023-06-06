import utils
import zappyAI as zp


class AI:
    _dead: bool = False
    _direction: zp.Direction = zp.Direction.N
    _comm: utils.Comm
    _pos: zp.Pos = zp.Pos(5, 5)
    _id: int
    _teamName: str
    _level: int = 1
    _world: zp.World
    _ticks: int = 0
    _inventory: zp.Resources = zp.Resources(0, 0, 0, 0, 0, 0, 0, 0)

    def __init__(self, comm: utils.Comm, team_name: str) -> None:
        self._comm = comm
        self._teamName = team_name
        data: list[str] = self._comm.recv()
        if data != ["WELCOME"]:
            raise ConnectionError("Invalid response")
        self._login(team_name)
        self.check_inventory()
        # init world with empty tiles from world size
        if self.connect_nbr() > 1:
            pass  # TODO: ask word info on broadcast

    def draw_map(self) -> None:
        print(self._world.__str__((self._pos, self._direction)))

    def _on_message(self, direction: zp.Direction, message: str) -> None:
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

    def _login(self, team_name: str) -> None:
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
        self._world = zp.World(zp.Size(res[1][0], res[1][1]))

    def _get_objects(self, data: str) -> list[zp.Resources]:
        objects: list[zp.Resources] = []
        if not data.startswith("[") or not data.endswith("]"):
            raise ValueError("Invalid message: " + data)
        tmp: list[str | None] = data[2:-2].split(",")
        for i in range(len(tmp)):
            if tmp[i] == "None":
                tmp[i] = None
                continue
            tmp[i] = tmp[i].strip()
        for index, objs in enumerate(tmp):
            if objs is None:
                objects.append(zp.Resources(0, 0, 0, 0, 0, 0, 0, 0))
                continue
            current = zp.Resources(0, 0, 0, 0, 0, 0, 0, 0)
            for idx, obj in enumerate(objs.split(" ")):
                if obj.strip() == "" or (index == 0 and idx == 0 and obj.strip() == "player"):
                    continue
                current[obj] += 1
            objects.append(current)
        return objects

    def forward(self) -> None:
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

    def right(self) -> None:
        self._comm.send("Right\n")
        self._ticks += 7
        if self._recv() != ["ok"]:
            raise ConnectionError("Invalid response")
        self._direction = zp.Direction(
            (self._direction.value + (1 if self._direction.value % 2 == 0 else 2) if self._direction.value < 6 else 1))

    def left(self) -> None:
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

    def look(self) -> None:
        nb_tiles: list[int] = [1, 3, 15, 24, 45, 72, 108, 162, 225, 324, 521]
        self._comm.send("Look\n")
        self._ticks += 7
        data: list[str] = self._recv()
        res: list[zp.Resources] = self._get_objects(data[0])
        if len(res) - 1 != nb_tiles[self._level]:
            raise ConnectionError("Invalid response")
        for lv in range(self._level + 1):
            for i in range(-lv, nb_tiles[lv] - lv):
                pos = self._at((lv, i))
                self._world[(pos[0], pos[1])] = zp.Tile(True, res.pop(0))

    def check_inventory(self) -> bool:
        self._comm.send("Inventory\n")
        self._ticks += 1
        success: bool = True
        data: list[str] = self._recv()
        datalist: list[str]
        if len(data) != 1:
            raise ConnectionError("Invalid response")
        if not data[0].startswith("[ ") or not data[0].endswith(" ]"):
            raise ConnectionError("Invalid response")
        data[0] = data[0][2:-2]
        datalist = data[0].split(", ")
        if len(datalist) != 7:
            raise ConnectionError("Invalid response")
        for string in datalist:
            key, value = string.strip().split(" ")
            if key not in self._inventory or not value.isdigit():
                raise ConnectionError("Invalid response")
            if int(value) != self._inventory[key]:
                success = False
            self._inventory[key] = int(value)
        return success

    def broadcast(self, message: str) -> None:
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

    def fork(self) -> None:
        self._comm.send("Fork\n")
        self._ticks += 42
        if self._recv() != ["ok"]:
            raise ConnectionError("Invalid response")

    def eject(self) -> None:
        self._comm.send("Eject\n")
        self._ticks += 7
        if self._recv() != ["ok"]:
            raise ConnectionError("Invalid response")

    def take(self, resource: zp.ObjectType) -> bool:
        if resource not in self._inventory:
            return False
        self._comm.send("Take " + str(resource) + "\n")
        self._ticks += 7
        res: list[str] = self._recv()
        if res == ["ok"]:
            self._inventory[resource] += 1
            self._world[(self._pos.y, self._pos.x)].objects[resource] -= 1
            if self._world[(self._pos.y, self._pos.x)].objects[resource] <= 0:
                self.look()
            return True
        elif res == ["ko"]:
            return False
        raise ConnectionError("Invalid response")

    def set(self, resource: zp.ObjectType) -> bool:
        if resource not in self._inventory or self._inventory[resource] <= 0:
            return False
        self._comm.send("Set " + str(resource) + "\n")
        self._ticks += 7
        res: list[str] = self._recv()
        if res == ["ok"]:
            self._inventory[resource] -= 1
            self._world[(self._pos.y, self._pos.x)].objects[resource] += 1
            return True
        elif res == ["ko"]:
            return False
        raise ConnectionError("Invalid response")

    def incantation(self) -> None:
        self._comm.send("Incantation\n")
        self._ticks += 300

    @property
    def pos(self) -> zp.Pos:
        return self._pos

    @property
    def world(self) -> zp.World:
        return self._world

    @property
    def inventory(self) -> zp.Resources:
        return self._inventory

    @property
    def level(self) -> int:
        return self._level

    @property
    def ticks(self) -> int:
        return self._ticks

    @property
    def direction(self) -> zp.Direction:
        return self._direction
