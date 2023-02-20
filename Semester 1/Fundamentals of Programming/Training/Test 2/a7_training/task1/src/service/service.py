import random

from task1.src.domain.domain import Complex


class Service:
    def __init__(self, repository):
        self.__repository = repository
        self.generate_random()

    def return_all(self):
        return self.__repository.get_all()

    def add_service(self, a, b):
        number = Complex(a, b)
        self.__repository.add(number)

    def delete_service(self, a, b):
        number = Complex(a, b)
        self.__repository.remove(number)

    def generate_random(self):
        for _ in range(10):
            number = Complex(random.randint(-100, 100), random.randint(-100, 100))
            try:
                self.__repository.add(number)
            except ValueError:
                continue

    def filter(self, start, end):
        new_list = []
        numbers = self.return_all()
        for i in range(start - 1, end):
            new_list.append(numbers[i])
        self.__repository.manipulate_list(new_list)

    def undo_service(self):
        return self.__repository.undo()
