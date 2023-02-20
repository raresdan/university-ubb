from dataclasses import dataclass


@dataclass
class Taxi:
    __id: int
    __x: int
    __y: int
    fare: int = 0

    def get_x(self):
        return self.__x

    def get_y(self):
        return self.__y

    def get_fare(self):
        return self.fare

    def get_id(self):
        return self.__id

    def set_x(self, new_x):
        self.__x = new_x

    def set_y(self, new_y):
        self.__y = new_y

    def set_fare(self, new_fare):
        self.fare = new_fare


@dataclass()
class Ride:
    __taxi_id: int
    __starting_x: int
    __starting_y: int
    __ending_x: int
    __ending_y: int

    def get_starting_x(self):
        return self.__starting_x

    def get_starting_y(self):
        return self.__starting_y

    def get_ending_x(self):
        return self.__ending_x

    def get_ending_y(self):
        return self.__ending_y

    def get_taxi_id(self):
        return self.__taxi_id

    def set_starting_x(self, new_x):
        self.__starting_x = new_x

    def set_starting_y(self, new_y):
        self.__starting_y = new_y

    def set_ending_x(self, new_x):
        self.__ending_x = new_x

    def set_ending_y(self, new_y):
        self.__ending_y = new_y

    def set_taxi_id(self, new_id):
        self.__taxi_id = new_id
