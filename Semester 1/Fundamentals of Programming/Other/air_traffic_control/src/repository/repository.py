from src.domain.domain import Flight


class Repository:
    def __init__(self):
        self.__all_flights = {}

    def get_all(self):
        return list(self.__all_flights.values())

    def find_by_id(self, entity_id):
        list_of_all = self.get_all()
        for flight in list_of_all:
            if entity_id == flight.get_id():
                return True
        return False

    def add_flight(self, flight: Flight):
        if self.find_by_id(flight.get_id()):
            raise ValueError('Duplicate entity')
        self.__all_flights[flight.get_id()] = flight

    def delete_flight(self, flight_id: Flight):
        if not self.find_by_id(flight_id):
            raise ValueError('Nonexisting entity')
        self.__all_flights.pop(flight_id)

    def update_flight(self, flight: Flight):
        if not self.find_by_id(flight.get_id()):
            raise ValueError('Nonexisting entity')
        self.__all_flights[flight.get_id()] = flight
