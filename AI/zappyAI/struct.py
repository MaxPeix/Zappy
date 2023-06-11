from dataclasses import dataclass


@dataclass
class Pos:
    x: int
    y: int

    def __dict__(self) -> dict:
        return {"x": self.x, "y": self.y}


@dataclass
class Size:
    width: int
    height: int

    def __dict__(self) -> dict:
        return {"width": self.width, "height": self.height}
