class Repository:
    def __init__(self):
        self.__all_reservations = {}

    def get_all(self):
        return list(self.__all_reservations.values())

    def find_by_id(self, reservation_id):
        if reservation_id in self.__all_reservations:
            return True
        return None

    def add(self, reservation):
        if self.find_by_id(reservation.get_id()) is not None:
            raise ValueError("Duplicate ID")
        self.__all_reservations[reservation.get_id] = reservation
