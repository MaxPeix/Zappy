from enum import Enum


class ObjectType(Enum):
    FOOD = 0
    LINEMATE = 1
    DERAUMERE = 2
    SIBUR = 3
    MENDIANE = 4
    PHIRAS = 5
    THYSTAME = 6
    PLAYER = 7


class Direction(Enum):
    def __str__(self):
        if self == Direction.N:
            return "North"
        elif self == Direction.NE:
            return "North-East"
        elif self == Direction.E:
            return "East"
        elif self == Direction.SE:
            return "South-East"
        elif self == Direction.S:
            return "South"
        elif self == Direction.SW:
            return "South-West"
        elif self == Direction.W:
            return "West"
        elif self == Direction.NW:
            return "North-West"
        else:
            return "Unknown"
    E = 1
    SE = 2
    S = 3
    SW = 4
    W = 5
    NW = 6
    N = 7
    NE = 8

