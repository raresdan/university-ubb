import random
from datetime import date

from src.domain.grade import Grade
from src.exception_class import CustomException


class GradeService:
    def __init__(self, grades_repository, students_repository, assignments_repository):
        self.__grades_repository = grades_repository
        self.__students_repository = students_repository
        self.__assignments_repository = assignments_repository
        self.generate_random_grades()

    def get_all_grades(self):
        return self.__grades_repository.find_all()

    def get_all_grades_student(self, student_id):
        return self.__grades_repository.find_by_student_id(student_id)

    def get_all_grades_assignment(self, assignment_id):
        return self.__grades_repository.find_by_assignment_id(assignment_id)

    def add_grade_service(self, student_id, assignment_id, grade):
        new_grade = Grade(student_id, assignment_id, grade)
        self.__grades_repository.add(new_grade)

    def update_grade_service(self, student_id, assignment_id, grade):
        new_grade = Grade(student_id, assignment_id, grade)
        self.__grades_repository.update(new_grade)

    def remove_grade_by_student_id(self, student_id):
        self.__grades_repository.remove_by_student_id(student_id)

    def remove_grade_by_assignment_id(self, assignment_id):
        self.__grades_repository.remove_by_assignment_id(assignment_id)

    def generate_random_grades(self):
        students = self.__students_repository.find_all()
        student_ids = []
        for student in students:
            student_ids.append(student.get_id())

        assignments = self.__assignments_repository.find_all()
        assignment_ids = []
        for assignment in assignments:
            assignment_ids.append(assignment.get_id())
        if len(assignment_ids) != 0 and len(student_ids) != 0:
            while len(list(self.get_all_grades())) < 20:
                try:
                    grade = Grade(random.choice(student_ids), random.choice(assignment_ids),
                                  random.randint(0, 10))
                    self.__grades_repository.add(grade)
                except ValueError:
                    continue

    def assign_student_service(self, student_id, assignment_id):
        students = self.__students_repository.find_all()
        student_ids = []
        for student in students:
            student_ids.append(student.get_id())
        assignments = self.__assignments_repository.find_all()
        assignment_ids = []
        for assignment in assignments:
            assignment_ids.append(assignment.get_id())
        if student_id not in student_ids:
            raise CustomException("Invalid student ID!")
        if assignment_id not in assignment_ids:
            raise CustomException("Invalid assignment ID!")
        grade = Grade(student_id, assignment_id)
        if grade not in self.__grades_repository.find_all():
            self.add_grade_service(student_id, assignment_id, None)

    def sorting_key(self, student, assignment_id):
        grades = [grade.get_grade() for grade in self.__grades_repository.find_by_student_id(student.get_id()) if
                  grade.get_assignment_id() == assignment_id and (
                          grade.get_grade() is not None or grade.get_grade() != 0)]
        if len(grades) == 0:
            return 0
        return max(grades)

    def statistic_by_assignment(self, assignment_id):
        if assignment_id not in [assignment.get_id() for assignment in self.__assignments_repository.find_all()]:
            raise CustomException(f"Invalid assignment ID! {assignment_id}")
        students_with_assignment = []
        for student in self.__students_repository.find_all():
            student_grades = [grade.get_grade() for grade in
                              self.__grades_repository.find_by_student_id(student.get_id()) if
                              grade.get_assignment_id() == assignment_id and grade.get_grade() is not None]
            if student_grades:
                students_with_assignment.append(student)
        students_with_assignment.sort(key=lambda s: self.sorting_key(s, assignment_id), reverse=True)
        return students_with_assignment

    def statistics_late_students(self):
        late_students = []
        current_day = date.today()
        for student in self.__students_repository.find_all():
            student_grades = self.__grades_repository.find_by_student_id(student.get_id())
            for grade in student_grades:
                assignment = self.__assignments_repository.find_by_id(grade.get_assignment_id())
                if grade.get_grade() is None and assignment.get_deadline() < current_day.day:
                    late_students.append(student)
                    break
        return late_students

    def statistic_best_students(self):
        students_with_grades = {}
        for grade in self.__grades_repository.find_all():
            student_id = grade.get_student_id()
            if student_id not in students_with_grades:
                students_with_grades[student_id] = []
            if grade.get_grade() is not None or grade.get_grade() != 0:
                students_with_grades[student_id].append(grade.get_grade())
        best_students = []
        for student_id, grades in students_with_grades.items():
            student = self.__students_repository.find_by_id(student_id)
            for grade in grades:
                if grade is None or grade == 0 or grade == "None":
                    grades.remove(grade)
            try:
                average_grade = round(sum(grades) / len(grades), 2)
            except ZeroDivisionError:
                return
            except TypeError:
                continue
            best_students.append((student, average_grade))
        best_students.sort(key=lambda s: s[1], reverse=True)
        return best_students
