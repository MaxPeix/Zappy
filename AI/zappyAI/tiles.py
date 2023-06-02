from zappyAI.objects import Object, Player
from dataclasses import dataclass


@dataclass
class Tile:
    def __str__(self):
        if not self.known:
            return "?"
        if len(self.objects) == 0:
            return " "
        elif Player in self.objects:
            return "P"
        else:
            return "!"
    known: bool
    objects: list[Object]
