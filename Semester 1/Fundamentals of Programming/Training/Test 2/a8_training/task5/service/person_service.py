import random

from task5.domain.person import Person


class PersonService:
    def __init__(self, repository):
        self.__repository = repository
        self.generate_random()

    def return_all(self):
        return self.__repository.get_all()

    def check_service(self, value):
        return self.__repository.check_value(value)

    def find_by_id_service(self, value):
        return self.__repository.find_by_id(value)

    def add_service(self, person_id, name, phone):
        person = Person(person_id, name, phone)
        self.__repository.add(person)

    def update_service(self, person_id, name, phone):
        person = Person(person_id, name, phone)
        self.__repository.update(person)

    def remove_service(self, person_id):
        self.__repository.remove_by_id(person_id)

    def generate_random(self):
        names = ["Mihai", "Andrei", "Dan", "Tudor", "Erik", "Andreea", "Alexia"]
        while len(self.return_all()) < 10:
            try:
                self.add_service(random.randint(10, 99), random.choice(names), random.randint(1000000000, 9999999999))
            except ValueError:
                continue
