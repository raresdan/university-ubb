import random

from domain.domain import Taxi, Ride


class Service:
    def __init__(self, taxis_repository, i):
        self.__repository = taxis_repository
        self.generate_random(i)

    @staticmethod
    def manhattan_distance(x1, y1, x2, y2):
        return abs((x1 - x2) + (y1 - y2))

    def get_all(self):
        return self.__repository.find_all()

    def generate_random(self, i):
        while len(list(self.get_all())) < i:
            try:
                self.add_taxi_service(random.randint(10, 99), random.randint(0, 100), random.randint(0, 100))
            except ValueError:
                continue

    def add_taxi_service(self, x, y, taxi_id):
        taxi = Taxi(x, y, taxi_id)
        self.__repository.add(taxi)

    def update_taxi_service(self, x, y, taxi_id):
        taxi = Taxi(x, y, taxi_id)
        self.__repository.update(taxi)

    def find_closest_ride(self, starting_x, starting_y):
        shortest = 1000000000000000000
        taxis = self.get_all()
        taxi_id = None
        for taxi in taxis:
            distance = self.manhattan_distance(taxi.get_x(), taxi.get_y(), starting_x, starting_y)
            if distance <= shortest:
                shortest = distance
                taxi_id = taxi.get_id()
        return taxi_id

    def add_ride(self, starting_x, starting_y, ending_x, ending_y):
        new_fare = self.manhattan_distance(starting_x, starting_y, ending_x, ending_y)
        taxi_id = self.find_closest_ride(starting_x, starting_y)
        taxi = self.__repository.find_by_id(taxi_id)
        taxi.set_fare(taxi.get_fare() + new_fare)
        taxi.set_x(ending_x)
        taxi.set_y(ending_y)
        return Ride(taxi_id, starting_x, starting_y, ending_x, ending_y), taxi

    def generate_random_rides(self, i):
        ride_list = []
        taxi_list = []
        for _ in range(i):
            starting_x = random.randint(0, 100)
            starting_y = random.randint(0, 100)
            ending_x = random.randint(0, 100)
            ending_y = random.randint(0, 100)
            try:
                ride, taxi = self.add_ride(starting_x, starting_y, ending_x, ending_y)
                ride_list.append(ride)
                taxi_list.append(taxi)
            except ValueError:
                continue
        return ride_list, taxi_list
