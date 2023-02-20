from dataclasses import dataclass


@dataclass
class Flight:
    identifier: str
    departure_city: str
    departure_time: str
    arrival_city: str
    arrival_time: str

    def get_id(self):
        return self.identifier

    def get_departure_city(self):
        return self.departure_city

    def get_departure_time(self):
        return self.departure_time

    def get_arrival_city(self):
        return self.arrival_city

    def get_arrival_time(self):
        return self.arrival_time