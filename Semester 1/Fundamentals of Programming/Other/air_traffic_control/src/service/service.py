from src.domain.domain import Flight


class Service:
    def __init__(self, repository):
        self.__repository = repository

    def return_all(self):
        return self.__repository.get_all()

    def add_service(self, flight_id, d_city, d_time, a_city, a_time):
        flight = Flight(flight_id, d_city, d_time, a_city, a_time)
        self.__repository.add_flight(flight)

    def delete_service(self, flight_id):
        self.__repository.delete_flight(flight_id)

    def update_service(self, flight_id, d_city, d_time, a_city, a_time):
        flight = Flight(flight_id, d_city, d_time, a_city, a_time)
        self.__repository.update_flight(flight)
