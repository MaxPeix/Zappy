from dataclasses import dataclass
from zappyAI.enums import *


@dataclass
class Object:
    type: ObjectType
    name: str
    description: str


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
