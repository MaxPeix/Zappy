from dataclasses import dataclass
from zappyAI.enums import *


@dataclass
class Object:
    type: ObjectType
    name: str
    description: str


@dataclass
class Player(Object):
    type: ObjectType = ObjectType.PLAYER
    name: str = "player"
    description: str = "A player"


@dataclass
class Linemate(Object):
    type: ObjectType = ObjectType.LINEMATE
    name: str = "linemate"
    description: str = "A linemate stone"


@dataclass
class Deraumere(Object):
    type: ObjectType = ObjectType.DERAUMERE
    name: str = "deraumere"
    description: str = "A deraumere stone"


@dataclass
class Sibur(Object):
    type: ObjectType = ObjectType.SIBUR
    name: str = "sibur"
    description: str = "A sibur stone"


@dataclass
class Mendiane(Object):
    type: ObjectType = ObjectType.MENDIANE
    name: str = "mendiane"
    description: str = "A mendiane stone"


@dataclass
class Phiras(Object):
    type: ObjectType = ObjectType.PHIRAS
    name: str = "phiras"
    description: str = "A phiras stone"


@dataclass
class Thystame(Object):
    type: ObjectType = ObjectType.THYSTAME
    name: str = "thystame"
    description: str = "A thystame stone"


@dataclass
class Food(Object):
    type: ObjectType = ObjectType.FOOD
    name: str = "food"
    description: str = "Somme food"


OBJECTS: list[tuple[str, Object]] = [
    ("linemate", Linemate()),
    ("deraumere", Deraumere()),
    ("sibur", Sibur()),
    ("mendiane", Mendiane()),
    ("phiras", Phiras()),
    ("thystame", Thystame()),
    ("food", Food()),
    ("player", Player())
]


def get_object(name: str) -> Object:
    for obj in OBJECTS:
        if obj[0] == name:
            return obj[1]
    else:
        raise ValueError("Invalid object name")


def is_object(name: str) -> bool:
    for obj in OBJECTS:
        if obj[0] == name:
            return True
    else:
        return False
