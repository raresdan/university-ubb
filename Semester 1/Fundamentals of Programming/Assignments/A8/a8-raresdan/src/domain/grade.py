from dataclasses import dataclass


@dataclass
class Grade:
    """
    Data Transfer Object?
    """
    __student_id: int
    __assignment_id: int
    __grade: int = None

    def get_student_id(self):
        return self.__student_id

    def get_assignment_id(self):
        return self.__assignment_id

    def get_grade(self):
        return self.__grade

    def set_grade(self, value):
        self.__grade = value
