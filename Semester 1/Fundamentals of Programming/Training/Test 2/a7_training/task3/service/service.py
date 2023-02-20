import random

from task3.domain.domain import Student


class Service:
    def __init__(self, repository):
        self.__repository = repository
        self.generate_random()

    def return_all(self):
        return self.__repository.get_all()

    def add_service(self, student_id, name, group):
        student = Student(student_id, name, group)
        self.__repository.add(student)

    def remove_service(self, student_id):
        self.__repository.remove_by_id(student_id)

    def generate_random(self):
        names = ["John", "Jane", "Mary", "James", "Oliver", "Mike", "Matthew"]
        while len(self.return_all()) < 10:
            try:
                self.add_service(random.randint(10, 99), random.choice(names), random.randint(911, 917))
            except ValueError:
                continue

    def remove_by_group(self, group):
        students = self.return_all()
        for student in students:
            if student.get_group() == group:
                try:
                    self.remove_service(student.get_id())
                except ValueError:
                    continue

