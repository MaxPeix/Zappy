from zappyAI.objects import Object
from dataclasses import dataclass


@dataclass
class Tile:
    x: int
    y: int
    objects: list[Object]
