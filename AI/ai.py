from connection import Comm
import zappyAI as zp


class AI:
    _comm: Comm
    _pos: zp.Pos
    _id: int
    _worldSize: zp.Size
    _teamName: str

    def __init__(self, comm: Comm, team_name: str):
        self._comm = comm
        self._teamName = team_name
        data: list[str] = self._comm.recv()
        if len(data) != 1 or data[0] != "WELCOME":
            raise ConnectionError("Invalid response")
        self._login(team_name)

    def _login(self, team_name: str):
        res: tuple[int, tuple[int, int]] = (0, (0, 0))
        data: list[str]

        self._comm.send(team_name + "\n")
        data = self._comm.recv()
        if len(data) != 2:
            raise ConnectionError("Invalid response")
        try:
            res = (int(data[0]), (int(data[1].split(" ")[0]), int(data[1].split(" ")[1])))
        except ValueError:
            raise ConnectionError("Invalid response")
        self._id = res[0]
        self._worldSize = zp.Size(res[1][0], res[1][1])

    def forward(self):
        self._comm.send("Forward\n")
        if self._comm.recv() != ["ok"]:
            raise ConnectionError("Invalid response")

    def right(self):
        self._comm.send("Right\n")
        if self._comm.recv() != ["ok"]:
            raise ConnectionError("Invalid response")

    def left(self):
        self._comm.send("Left\n")
        if self._comm.recv() != ["ok"]:
            raise ConnectionError("Invalid response")

    def look(self) -> list[list[zp.Object]]:
        res: list[list[zp.Object]] = []
        self._comm.send("Look\n")
        return res

    def inventory(self) -> list[zp.Object]:
        res: list[zp.Object] = []
        self._comm.send("Inventory\n")
        return res

    def broadcast(self, message: str):
        self._comm.send("Broadcast " + message + "\n")

    def connect_nbr(self):
        self._comm.send("Connect_nbr\n")

    def fork(self):
        self._comm.send("Fork\n")

    def eject(self):
        self._comm.send("Eject\n")

    def take(self, resource: zp.objects):
        self._comm.send("Take " + resource.name + "\n")

    def set(self, resource: zp.objects):
        self._comm.send("Set " + resource.name + "\n")

    def incantation(self):
        self._comm.send("Incantation\n")
