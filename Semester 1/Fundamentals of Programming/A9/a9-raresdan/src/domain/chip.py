from dataclasses import dataclass


@dataclass
class Chip:
    __color: str

    def get_color(self):
        return self.__color

