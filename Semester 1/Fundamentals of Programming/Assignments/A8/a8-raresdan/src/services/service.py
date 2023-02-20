import random

from src.domain.entities import Assignment, Student


class StudentService:
    def __init__(self, student_repository):
        self.__student_repository = student_repository
        self.generate_random_students()

    def get_all_students(self):
        return self.__student_repository.find_all()

    def add_student_service(self, student_id, name, group):
        student = Student(student_id, name, group)
        self.__student_repository.add(student)

    def update_student_service(self, student_id, name, group):
        student = Student(student_id, name, group)
        self.__student_repository.update(student)

    def remove_student_service(self, student_id):
        self.__student_repository.remove_by_id(student_id)

    def generate_random_students(self):
        names = ["Liam", "Olivia", "Noah", "Emma", "Oliver", "Charlotte", "Elijah", "Amelia", "James", "Ava", "William",
                 "Sophia", "Benjamin", "Isabella", "Lucas", "Mia", "Henry", "Evelyn", "Theodore", "Harper", "Dan"]
        while len(list(self.get_all_students())) < 10:
            try:
                self.add_student_service(random.randint(100, 999), random.choice(names), random.randint(911, 917))
            except ValueError:
                continue


class AssignmentService:
    def __init__(self, assignment_repository):
        self.__assignment_repository = assignment_repository
        self.generate_random_assignments()

    def get_all_assignments(self):
        return self.__assignment_repository.find_all()

    def add_assignment_service(self, assignment_id, description, deadline):
        assignment = Assignment(assignment_id, description, deadline)
        self.__assignment_repository.add(assignment)

    def update_assignment_service(self, assignment_id, description, deadline):
        assignment = Assignment(assignment_id, description, deadline)
        self.__assignment_repository.update(assignment)

    def remove_assignment_service(self, assignment_id):
        self.__assignment_repository.remove_by_id(assignment_id)

    def generate_random_assignments(self):
        descriptions = ["Fundamentals of Programming", "Mathematical Analysis", "Linear Algebra",
                        "Computer System Arhitecture", "Computational Logic", "Object Oriented Programming",
                        "C Programming", "Data Structures & Algorithms", "Dynamic Systems", "Operational Systems",
                        "Geometry", "Graph's Theory"]
        while len(list(self.get_all_assignments())) < 10:
            try:
                self.add_assignment_service(random.randint(10, 99), random.choice(descriptions), random.randint(1, 31))
            except ValueError:
                continue
