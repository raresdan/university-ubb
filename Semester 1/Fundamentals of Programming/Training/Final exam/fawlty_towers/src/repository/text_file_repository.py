from src.domain.reservation import Reservation
from src.repository.repository import Repository


class TextFileRepository(Repository):
    def __init__(self):
        super().__init__()
        self.__file_name = "reservations"
        self.__load_data()

    def __load_data(self):
        with open(self.__file_name) as f:
            for line in f:
                line.strip()
                array = line.split(",")
                reservation = Reservation(int(array[0]), int(array[1]), array[2], int(array[3]), array[4], array[5])
                try:
                    super().add(reservation)
                except ValueError:
                    continue
        f.close()

    def add(self, reservation):
        super().add(reservation)
        with open(self.__file_name, "a") as f:
            f.write(str(reservation.get_id()) + "," + str(reservation.get_room_number()) + "," + str(
                reservation.get_family_name()) + "," + str(reservation.get_guests()) + "," + str(
                reservation.get_arrival()) + "," + str(
                reservation.get_departure()) + "\n")
        f.close()
