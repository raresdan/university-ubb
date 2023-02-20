from src.exception_class import CustomException


class Ui:
    def __init__(self, student_service, assignment_service, grades_service):
        self.__student_service = student_service
        self.__assignment_service = assignment_service
        self.__grades_service = grades_service

    @staticmethod
    def menu():
        print("------------------MENU------------------")
        print()
        print("Manipulate Students")
        print()
        print("add student - Add a student to the list of students")
        print("list students - Show the list of all the students")
        print("delete student - Delete a student from the students list, but also his grades")
        print("update student - Update student data")
        print()
        print("Manipulate Assignments")
        print()
        print("add assignment - Add an assignment to the list of assignments")
        print("list assignments - Show the list of all the assignments")
        print("delete assignment - Delete an assignment from the assignments list, but also from the list of grades")
        print("update assignment - Update assignment data")
        print()
        print("Manipulate Lab Work")
        print()
        print("list grades - Show the list of all the grades")
        print("assign student - Assign a certain student a certain assignment")
        print("assign group - Assign a certain group of students a certain assignment")
        print("grade assignment - Grade ungraded assignments")
        print()
        print("Statistics")
        print()
        print("stats assignment - grades of all students who received a given assignment")
        print("stats late - all students who have at least one late assignment")
        print("stats best - all students ordered based on their average grade")
        print()
        print("exit - Exit the application")

    def add_student(self):
        student_id = input("Enter student's ID: ")
        try:
            student_id = int(student_id)
        except ValueError as ve:
            print("Invalid student's ID! ", ve)
            return
        name = input("Enter student's name: ")
        try:
            name = str(name)
        except ValueError as ve:
            print("Invalid student name! ", ve)
            return
        group = input("Enter student's group: ")
        try:
            group = int(group)
        except ValueError as ve:
            print("Invalid student's group! ", ve)
            return
        try:
            self.__student_service.add_student_service(student_id, name, group)
        except ValueError as ve:
            print(ve)
            return

    def list_students(self):
        students = self.__student_service.get_all_students()
        for student in students:
            print(f"ID: {student.get_id()} Name: {student.get_name()} Group: {student.get_group()}")

    def delete_student(self):
        student_id = input("Enter ID for student you want to delete: ")
        try:
            student_id = int(student_id)
        except ValueError as ve:
            print("Invalid student's ID! ", ve)
            return
        try:
            self.__student_service.remove_student_service(int(student_id))
            print("Student was deleted from the student list!")
        except ValueError as ve:
            print(ve)
            return
        try:
            self.__grades_service.remove_grade_by_student_id(int(student_id))
            print("Student's grades were deleted from the grades list!")
        except ValueError as ve:
            print(ve)
            return

    def update_student(self):
        student_id = input("Enter ID for student you want to update: ")

        try:
            student_id = int(student_id)
        except ValueError as ve:
            print("Invalid student's ID! ", ve)
            return
        name = input("Enter new student's name: ")
        try:
            name = str(name)
        except ValueError as ve:
            print("Invalid student name! ", ve)
            return
        group = input("Enter new student's group: ")
        try:
            group = int(group)
        except ValueError as ve:
            print("Invalid student's group! ", ve)
            return
        try:
            self.__student_service.update_student_service(student_id, name, group)
        except ValueError as ve:
            print(ve)
            return

    def add_assignment(self):
        assignment_id = input("Enter assignment's ID: ")
        try:
            assignment_id = int(assignment_id)
        except ValueError as ve:
            print("Invalid assignment's ID! ", ve)
            return
        description = input("Enter assignment's description: ")
        try:
            description = str(description)
        except ValueError as ve:
            print("Invalid assignment's description! ", ve)
            return
        deadline = input("Enter assignment's deadline: ")
        try:
            deadline = int(deadline)
        except ValueError as ve:
            print("Invalid assignment's deadline! ", ve)
            return
        if deadline < 1 or deadline > 30:
            print("Invalid deadline input! Not between 1 and 30!")
            return
        try:
            self.__assignment_service.add_assignment_service(assignment_id, description, deadline)
        except ValueError as ve:
            print(ve)
            return

    def list_assignments(self):
        assignments = self.__assignment_service.get_all_assignments()
        for assignment in assignments:
            print(
                f"ID: {assignment.get_id()} Description: {assignment.get_description()} Deadline: {assignment.get_deadline()}")

    def delete_assignment(self):
        assignment_id = input("Enter ID for assignment you want to delete: ")
        try:
            assignment_id = int(assignment_id)
        except ValueError as ve:
            print("Invalid assignment's ID! ", ve)
            return
        try:
            self.__assignment_service.remove_assignment_service(assignment_id)
            print("Assignment was deleted from the assignment list!")
        except ValueError as ve:
            print(ve)
            return
        try:
            self.__grades_service.remove_grade_by_assignment_id(assignment_id)
            print("Assignment's grades were deleted from the grades list!")
        except ValueError as ve:
            print(ve)
            return

    def update_assignment(self):
        assignment_id = input("Enter ID for assignment you want to update: ")
        try:
            assignment_id = int(assignment_id)
        except ValueError as ve:
            print("Invalid assignment's ID! ", ve)
            return

        description = input("Enter new assignment's description: ")
        try:
            description = str(description)
        except ValueError as ve:
            print("Invalid assignment's description! ", ve)
            return
        deadline = input("Enter new assignment's deadline: ")
        try:
            deadline = int(deadline)
        except ValueError as ve:
            print("Invalid assignment's deadline! ", ve)
            return
        try:
            self.__assignment_service.update_assignment_service(assignment_id, description, deadline)
        except ValueError as ve:
            print(ve)
            return

    def assign_student(self):
        student_id = input("Enter ID for the student you want to give an assignment: ")
        try:
            student_id = int(student_id)
        except ValueError as ve:
            print("Invalid student's ID! ", ve)
            return
        assignment_id = input("Enter ID for the assignment you want to give to the student: ")
        try:
            assignment_id = int(assignment_id)
        except ValueError as ve:
            print("Invalid assignment's ID! ", ve)
            return
        try:
            self.__grades_service.assign_student_service(student_id, assignment_id)
        except CustomException as ve:
            print(ve)
            return

    def assign_group(self):
        group = input("Enter the group you want to give an assignment: ")
        try:
            group = int(group)
        except ValueError as ve:
            print("Invalid student's group! ", ve)
            return
        assignment_id = input("Enter ID for the assignment you want to give to the student: ")
        try:
            assignment_id = int(assignment_id)
        except ValueError as ve:
            print("Invalid assignment's ID! ", ve)
            return
        students = self.__student_service.get_all_students()
        for student in students:
            if student.get_group() == group:
                try:
                    self.__grades_service.add_grade_service(student.get_id(), assignment_id, None)
                except ValueError as ve:
                    print(ve)
                    return

    def grade_assignment(self):
        grades = self.__grades_service.get_all_grades()
        student_id = input("Enter ID for the student you want to grade: ")
        try:
            student_id = int(student_id)
        except ValueError as ve:
            print("Invalid student's ID! ", ve)
            return
        assignment_id = input("Enter ID for the assignment you want to grade: ")
        try:
            assignment_id = int(assignment_id)
        except ValueError as ve:
            print("Invalid assignment's ID! ", ve)
            return
        for grade in grades:
            if grade.get_student_id() == int(student_id) and grade.get_assignment_id() == int(assignment_id):
                if grade.get_grade() == 0 or grade.get_grade() is None:
                    new_grade = int(input("Grade assignment: "))
                    try:
                        new_grade == int(new_grade)
                    except ValueError as ve:
                        print("Grade must be integer!", ve)
                        return
                    if int(new_grade) < 1 or int(new_grade) > 10:
                        print("Grade must be between 1 and  10!")
                        return
                    self.__grades_service.update_grade_service(student_id, assignment_id, new_grade)
                    return
                else:
                    print("The assignment is already graded!")
                    return
        print("Invalid combination of IDs!")
        return

    def list_grades(self):
        grades = self.__grades_service.get_all_grades()
        for grade in grades:
            if grade.get_grade() == 0:
                grade.set_grade(None)
            print(
                f"Student ID: {grade.get_student_id()} Assignment ID: {grade.get_assignment_id()} Grade: {grade.get_grade()}")

    def statistic_assignment(self):
        assignment_id = input("Enter ID for the assignment you want to see statistics: ")
        try:
            assignment_id = int(assignment_id)
        except ValueError as ve:
            print("Invalid assignment's ID! ", ve)
            return
        try:
            stats = self.__grades_service.statistic_by_assignment(int(assignment_id))
        except CustomException as ve:
            print(ve)
            return
        index = 1
        for student in stats:
            if student is not None:
                print(
                    f"#{index} ID: {student.get_id()} Name: {student.get_name()} Group: {student.get_group()}")
            index = index + 1

    def statistic_late(self):
        try:
            stats = self.__grades_service.statistics_late_students()
        except ValueError as ve:
            print(ve)
            return
        if not stats:
            print("No student has late assignments!")
        else:
            for student in stats:
                if student is not None:
                    print(
                        f"ID: {student.get_id()} Name: {student.get_name()} Group: {student.get_group()}")

    def statistic_best_grades(self):
        try:
            stats = self.__grades_service.statistic_best_students()
        except ValueError as ve:
            print(ve)
            return
        index = 1
        for student in stats:
            if student is not None:
                print(
                    f"#{index} ID: {student[0].get_id()} Name: {student[0].get_name()} Group: {student[0].get_group()} Average Grade: {student[1]}")
            index = index + 1

    def run_menu(self):
        self.menu()
        while True:
            while True:
                try:
                    print()
                    option = input("Enter the command corresponding to the desired action: ")
                    print()
                    break
                except ValueError:
                    print("Invalid command!")
            if option.lower().strip() == "add student":
                self.add_student()
            elif option.lower().strip() == "list students":
                self.list_students()
            elif option.lower().strip() == "delete student":
                self.delete_student()
            elif option.lower().strip() == "update student":
                self.update_student()

            elif option.lower().strip() == "add assignment":
                self.add_assignment()
            elif option.lower().strip() == "list assignments":
                self.list_assignments()
            elif option.lower().strip() == "delete assignment":
                self.delete_assignment()
            elif option.lower().strip() == "update assignment":
                self.update_assignment()

            elif option.lower().strip() == "list grades":
                self.list_grades()
            elif option.lower().strip() == "assign student":
                self.assign_student()
            elif option.lower().strip() == "assign group":
                self.assign_group()
            elif option.lower().strip() == "grade assignment":
                self.grade_assignment()

            elif option.lower().strip() == "stats assignment":
                self.statistic_assignment()
            elif option.lower().strip() == "stats late":
                self.statistic_late()
            elif option.lower().strip() == "stats best":
                self.statistic_best_grades()

            elif option.lower().strip() == "exit":
                print("The menu was exited successfully!")
                break
            else:
                print("Invalid command!")
