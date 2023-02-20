class GradeRepository:
    def __init__(self):
        self.__all_grades = {}

    def find_all(self):
        return list(self.__all_grades.values())

    def find_by_student_id(self, student_id):
        """
        searches a student by the id
        :param student_id: the student id searched for
        :return: a list of all the grades of the student with student id
        """
        grades = []
        for grade in self.__all_grades.values():
            if grade.get_student_id() == student_id:
                grades.append(grade)
        return grades

    def find_by_assignment_id(self, assignment_id):
        """
        searches assignments by id
        :param assignment_id: the assignment id searched for
        :return: a list of all the grades of an assignment with student id
        """
        grades = []
        for grade in self.__all_grades.values():
            if grade.get_assignment_id() == assignment_id:
                grades.append(grade)
        return grades

    def add(self, grade):
        """
        add a grade to the dict of grades
        :param grade: the grade we want to add
        :return: adds the grade or raises ValueError if there already is a grade with that id
        """
        if (grade.get_student_id(), grade.get_assignment_id()) in self.__all_grades:
            raise ValueError("Duplicate IDs! These IDs already exist!")
        self.__all_grades[(grade.get_student_id(), grade.get_assignment_id())] = grade

    def update(self, grade):
        """
        updates a grade in the dict of grades
        :param grade: the grade we want to update
        :return: updates the grade or raises ValueError if there doesn't already exist a grade with that id
        """
        if (grade.get_student_id(), grade.get_assignment_id()) not in self.__all_grades:
            raise ValueError("Invalid ID! The ID does not exist!")
        self.__all_grades[(grade.get_student_id(), grade.get_assignment_id())] = grade

    def remove_by_student_id(self, student_id):
        """
        deletes all grades of a student
        :param student_id: the id of the student which grades we want to delete
        :return: deletes all the students with student id from the dict of grades
        """
        removed = False
        for key in list(self.__all_grades.keys()):
            if key[0] == student_id:
                del self.__all_grades[key]
                removed = True
        if not removed:
            raise ValueError("Invalid Student ID! The ID does not exist!")

    def remove_by_assignment_id(self, assignment_id):
        """
        deletes all grades of an assignment
        :param assignment_id: the id of the assignment which grades we want to delete
        :return: deletes all the assignments with student id from the dict of grades
        """
        removed = False
        for key in list(self.__all_grades.keys()):
            if key[1] == assignment_id:
                del self.__all_grades[key]
                removed = True
        if not removed:
            raise ValueError("Invalid Assignment ID! The ID does not exist!")
