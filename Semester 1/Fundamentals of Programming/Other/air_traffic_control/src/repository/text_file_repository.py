from src.domain.domain import Flight
from src.repository.repository import Repository


class TextFileRepository(Repository):
    def __init__(self):
        super().__init__()
        self.__file_name = "D:\\_DOCUMENTE_RARES\\Desktop\\air_traffic_control\\src\\input"
        self.__load_data()

    def __load_data(self):
        with open(self.__file_name) as f:
            for line in f:
                line = line.strip()
                array = line.split(",")
                flight = Flight(array[0], array[1], array[2], array[3], array[4])
                super().add_flight(flight)

    def add_flight(self, flight):
        super().add_flight(flight)
        with open(self.__file_name, "a") as f:
            f.write(str(flight.get_id()) + "," + str(flight.get_departure_city()) + "," + str(
                flight.get_departure_time()) + "," + str(flight.get_arrival_city()) + "," + str(
                flight.get_arrival_time()) + "\n")

    def delete_flight(self, flight_id):
        super().delete_flight(flight_id)
        new_flights = self.get_all()
        with open(self.__file_name, "w") as f:
            for flight in new_flights:
                f.write(str(flight.get_id()) + "," + str(flight.get_departure_city()) + "," + str(
                    flight.get_departure_time()) + "," + str(flight.get_arrival_city()) + "," + str(
                    flight.get_arrival_time()) + "\n")
