from dataclasses import dataclass


@dataclass
class Pos:
    x: int
    y: int


@dataclass
class Size:
    width: int
    height: int
