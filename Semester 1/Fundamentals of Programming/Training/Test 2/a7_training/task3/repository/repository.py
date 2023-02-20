import copy


class Repository:
    def __init__(self):
        self.__all_students = {}

    def get_all(self):
        return list(self.__all_students.values())

    def find_by_id(self, student_id):
        if student_id in self.__all_students:
            return self.__all_students[student_id]
        return None

    def add(self, student):
        if self.find_by_id(student.get_id()) is not None:
            raise ValueError("Duplicate ID!")
        self.__all_students[student.get_id()] = student

    def update(self, student):
        if self.find_by_id(student.get_id()) is None:
            raise ValueError("Duplicate ID!")
        self.__all_students[student.get_id()] = student

    def remove_by_id(self, student_id):
        if self.find_by_id(student_id) is None:
            raise ValueError("Duplicate ID!")
        del self.__all_students[student_id]


