from dataclasses import dataclass


@dataclass
class Player:
    __name: str
    __chip: str

    def get_name(self):
        return self.__name

    def get_chip(self):
        return self.__chip

    def __str__(self):
        return f"Player {self.__name} is playing with {self.__chip}!"
