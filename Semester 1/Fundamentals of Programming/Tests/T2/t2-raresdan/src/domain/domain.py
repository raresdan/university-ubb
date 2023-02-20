from dataclasses import dataclass


@dataclass
class Address:
    __address_id: int
    __name: str
    __number: int
    __x: int
    __y: int

    def get_id(self):
        return self.__address_id

    def get_name(self):
        return self.__name

    def get_number(self):
        return self.__number

    def get_x(self):
        return self.__x

    def get_y(self):
        return self.__y
