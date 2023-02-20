from math import sqrt

from src.domain.domain import Address


class Service:
    def __init__(self, repository):
        self.__repository = repository

    @staticmethod
    def euclidian_distance(x1, y1, x2, y2):
        return round(sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2), 2)

    def return_all(self):
        return self.__repository.get_all()

    def add_service(self, address_id, name, number, x, y):
        address = Address(address_id, name, number, x, y)
        self.__repository.add(address)

    def stations(self, x, y, d):
        """

        :param x: user input of the first coordinate
        :param y: user input of the second coordinate
        :param d: distance
        :return: list of addresses that have the distance at most d from the given point
        """

        address_list = []
        distance_list = []
        addresses = self.return_all()
        for address in addresses:
            distance = self.euclidian_distance(x, y, address.get_x(), address.get_y())
            if distance < d:
                address_list.append(address)
                distance_list.append(distance)
        return address_list, distance_list

    def minimum_distance(self):
        """
        Calculates the mean of all coordinates to find where to place the taxi station
        :return: both coordinates x, y of the new taxi station
        """

        mean_x = 0
        mean_y = 0
        addresses = self.return_all()
        for address in addresses:
            mean_x += address.get_x()
            mean_y += address.get_y()
        final_x = mean_x // len(self.return_all())
        final_y = mean_y // len(self.return_all())
        if final_y > 100:
            final_y = 100
        if final_x > 100:
            final_x = 100
        return final_x, final_y
