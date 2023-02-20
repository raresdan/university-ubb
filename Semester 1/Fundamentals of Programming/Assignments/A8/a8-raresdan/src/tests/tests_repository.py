from unittest import TestCase

from src.domain.entities import Student, Assignment
from src.repository.repository import GenericRepository


class TestStudentRepository(TestCase):
    def setUp(self):
        self.student_repository = GenericRepository()
        self.student1 = Student(1, "John", 911)
        self.student2 = Student(2, "Jane", 912)
        self.student3 = Student(3, "Bob", 913)

    def test_add_student(self):
        self.student_repository.add(self.student1)
        self.assertEqual(len(self.student_repository.find_all()), 1)
        self.student_repository.add(self.student2)
        self.assertEqual(len(self.student_repository.find_all()), 2)
        self.assertRaises(ValueError, self.student_repository.add, self.student1)

    def test_update_student(self):
        self.student_repository.add(self.student1)
        self.student_repository.update(Student(1, "James", 914))
        self.assertEqual(self.student_repository.find_by_id(1).get_group(), 914)
        self.assertRaises(ValueError, self.student_repository.update, Student(5, "James", 914))

    def test_remove_student(self):
        self.student_repository.add(self.student1)
        self.student_repository.add(self.student2)
        self.student_repository.remove_by_id(1)
        self.assertEqual(len(self.student_repository.find_all()), 1)
        self.assertRaises(ValueError, self.student_repository.remove_by_id, 5)

    def tearDown(self) -> None:
        pass


class TestAssignmentRepository(TestCase):
    def setUp(self):
        self.assignment_repository = GenericRepository()
        self.assignment1 = Assignment(1, "Homework 1", 14)
        self.assignment2 = Assignment(2, "Homework 2", 15)
        self.assignment3 = Assignment(3, "Homework 3", 16)

    def test_add_assignment(self):
        self.assignment_repository.add(self.assignment1)
        self.assertEqual(len(self.assignment_repository.find_all()), 1)
        self.assignment_repository.add(self.assignment2)
        self.assertEqual(len(self.assignment_repository.find_all()), 2)

    def test_update_assignment(self):
        self.assignment_repository.add(self.assignment1)
        self.assignment_repository.update(Assignment(1, "Homework 1", 17))
        self.assertEqual(self.assignment_repository.find_by_id(1).get_deadline(), 17)

    def test_remove_assignment(self):
        self.assignment_repository.add(self.assignment1)
        self.assignment_repository.add(self.assignment2)
        self.assignment_repository.remove_by_id(1)
        self.assertEqual(len(self.assignment_repository.find_all()), 1)

    def tearDown(self) -> None:
        pass
