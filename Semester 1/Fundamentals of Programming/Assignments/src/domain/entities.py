"""
Write an application that manages student lab assignments for a discipline. The application will store:

Student: student_id, name, group
Assignment: assignment_id, description, deadline
Grade: assignment_id, student_id, grade_value

Create an application that allows to:

Manage students and assignments. The user can add, remove, update, and list both students and assignments.
Give assignments to a student or a group of students.
In case an assignment is given to a group of students, every student in the group will receive it.
In case there are students who were previously given that assignment, it will not be assigned again.
Grade student for a given assignment.
When grading, the program must allow the user to select the assignment that is graded, from the student’s list of ungraded assignments.
A student’s grade for a given assignment cannot be changed.
Create statistics:
All students who received a given assignment, ordered descending by grade.
All students who are late in handing in at least one assignment. These are all the students who have an ungraded assignment for which the deadline has passed.
Students with the best school situation, sorted in descending order of the average grade received for all graded assignments.
"""
from dataclasses import dataclass


@dataclass
class Student:
    __student_id: int
    __name: str
    __group: int

    def get_id(self):
        return self.__student_id

    def get_name(self):
        return self.__name

    def get_group(self):
        return self.__group

    def set_name(self, value):
        self.__name = value

    def set_group(self, value):
        self.__group = value


@dataclass
class Assignment:
    __assignment_id: int
    __description: str
    __deadline: int

    def get_id(self):
        return self.__assignment_id

    def get_description(self):
        return self.__description

    def get_deadline(self):
        return self.__deadline

    def set_description(self, value):
        self.__description = value

    def set_deadline(self, value):
        self.__deadline = value
