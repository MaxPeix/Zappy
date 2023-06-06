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

    def __repr__(self):
        return str(self)

    def __len__(self):
        return len(self.objects)

    def __getitem__(self, item: ObjectType | str) -> int:
        return self.objects[item]

    def __setitem__(self, item: ObjectType | str, value: int):
        self.objects[item] = value

    def __iter__(self):
        for item in self.objects:
            for i in range(self.objects[item]):
                yield item
