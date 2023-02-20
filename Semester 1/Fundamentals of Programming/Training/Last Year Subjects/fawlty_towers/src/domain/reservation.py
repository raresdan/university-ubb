from dataclasses import dataclass


@dataclass
class Reservation:
    reservation_id: int
    room_number: int
    family_name: str
    guests: int
    arrival: str
    departure: str

    def get_id(self):
        return self.reservation_id

    def get_room_number(self):
        return self.room_number

    def get_family_name(self):
        return self.family_name

    def get_guests(self):
        return self.guests

    def get_arrival(self):
        return self.arrival

    def get_departure(self):
        return self.departure
