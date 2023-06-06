from zappyAI.objects import Resources
from zappyAI.enums import ObjectType
from dataclasses import dataclass


@dataclass
class Tile:
    known: bool
    objects: Resources

    def __str__(self):
        if not self.known:
            return "?"
        if len(self.objects) == 0:
            return " "
        elif self.objects[ObjectType.PLAYER] > 0:
            return "P"
        else:
            return "!"
