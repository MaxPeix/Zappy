from zappyAI.objects import Resources
from zappyAI.enums import ObjectType
from dataclasses import dataclass


@dataclass
class Tile:
    def __str__(self):
        if not self.known:
            return "?"
        if len(self.objects) == 0:
            return " "
        elif ObjectType.PLAYER in self.objects:
            return "P"
        else:
            return "!"
    known: bool
    objects: Resources
