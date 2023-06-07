from enum import Enum
from itertools import cycle


class ObjectType(Enum):
    FOOD = 0
    LINEMATE = 1
    DERAUMERE = 2
    SIBUR = 3
    MENDIANE = 4
    PHIRAS = 5
    THYSTAME = 6
    PLAYER = 7

    def __str__(self):
        if self == ObjectType.FOOD:
            return "food"
        elif self == ObjectType.LINEMATE:
            return "linemate"
        elif self == ObjectType.DERAUMERE:
            return "deraumere"
        elif self == ObjectType.SIBUR:
            return "sibur"
        elif self == ObjectType.MENDIANE:
            return "mendiane"
        elif self == ObjectType.PHIRAS:
            return "phiras"
        elif self == ObjectType.THYSTAME:
            return "thystame"
        elif self == ObjectType.PLAYER:
            return "player"
        else:
            return "unknown"

    def __repr__(self):
        return str(self)


class Direction(Enum):

    def __lt__(self, other: 'Direction') -> bool:
        enum_list = list(Direction)
        enum_list_rev = list(Direction)
        enum_list_rev.reverse()
        enum_list = cycle(enum_list)
        enum_list_rev = cycle(enum_list_rev)
        i: int = 0
        j: int = 0

        if self == other:
            return False
        while next(enum_list) != self:
            pass
        while next(enum_list) != other:
            i = i + 1
        while next(enum_list_rev) != self:
            pass
        while next(enum_list_rev) != other:
            j = j + 1
        if i < j:
            return True
        return False

    def __gt__(self, other: 'Direction') -> bool:
        if self == other:
            return False
        return not self < other

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
