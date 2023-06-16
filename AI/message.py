from dataclasses import dataclass
import json
from typing import Callable
import os

from . import brain


@dataclass
class HANDLER:
    _name: str
    _recv: Callable
    _send: Callable
    _msg: 'Message'

    def to_json(self, ans: bool = False, to: int | None = None, *args, **kwargs) -> str | None:
        data: str | None = self._send(self, *args, **kwargs)
        if data is None:
            return None
        if data == "null":
            data = None
        res: dict = {
            "from": os.getpid(),
            "to": to,
            "ans": ans,
            "what": self._name,
            "data": json.dumps(data)
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
    _brain: brain.Brain
    HANDLERS: dict[str, HANDLER]

    def __init__(self, brain: brain.Brain):
        self._brain = brain
        self["new master"] = (self.recv_bootstrap_master, self.send_bootstrap_master)

    def __getitem__(self, item):
        return self.HANDLERS[item]

    def __setitem__(self, key, value: tuple[Callable, Callable]):
        self.HANDLERS[key] = HANDLER(self, key, value[0], value[1])

    def recv_bootstrap_master(self, direction: zp.Direction, msg: dict) -> None:
        if not msg["ans"]:
            self._brain.ai.broadcast(self["new master"].to_json(True, int(msg["from"])))
            return
        if msg["data"] is None:
            print("no master yet")
            if self._brain.ai.role == zp.Role.MASTER:
                self._brain.ai.broadcast(self["new master"].to_json(True, int(msg["from"])))
            return
        if self._brain.ai.role == zp.Role.MASTER:
            self._brain.ai.role = zp.Role.WORKER
            return
        self._brain.ai.master_id = int(msg["data"])

    def send_bootstrap_master(self) -> str | None:
        if self._brain.ai.role == zp.Role.MASTER:
            return str(os.getpid())
        if self._brain.ai.master_id is None:
            return "null"
        return str(self._brain.ai.master_id)
