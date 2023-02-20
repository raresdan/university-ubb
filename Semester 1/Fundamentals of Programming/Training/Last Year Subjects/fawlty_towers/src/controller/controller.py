import random

from src.domain.reservation import Reservation


class Controller:
    def __init__(self, repository):
        self.__repository = repository

    def return_all(self):
        return self.__repository.get_all()

    def add(self, fn, g, a, d):
        rid = self.generate_id()

        reservation = Reservation(rid, random.randint(1, 5), fn, g, a, d)
        self.__repository.add(reservation)

    def generate_id(self):
        rid = random.randint(1000, 9999)
        while self.__repository.find_by_id(rid) is not None:
            rid = random.randint(1000, 9999)
        return rid

    def find_free_room(self, g, a, d):
        all_rooms = self.return_all()
        suitable_rooms = []
        for room in all_rooms:
            if room.get_guest() == g:
                suitable_rooms.append(room)

    def is_free(self, rid, a, d):
        room = self.__repository.find_by_id(rid)
        arrival = a.split(".")
        departure = d.split(".")
        room_arrival = room.get_arrival().split(".")
        room_departure = room.get_departure().split(".")
