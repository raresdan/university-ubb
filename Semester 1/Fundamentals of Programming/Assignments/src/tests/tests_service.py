from unittest import TestCase

from src.repository.repository import GenericRepository
from src.services.service import StudentService, AssignmentService


class TestStudentService(TestCase):
    def setUp(self):
        self.student_repository = GenericRepository()
        self.student_service = StudentService(self.student_repository)

    def test_add_student_service(self):
        self.student_service.add_student_service(100, "John", 911)
        students = self.student_repository.find_all()
        self.assertEqual(len(students), 11)
        self.assertEqual(students[10].get_id(), 100)
        self.assertEqual(students[10].get_name(), "John")
        self.assertEqual(students[10].get_group(), 911)
        self.assertRaises(ValueError, self.student_service.add_student_service, 100, "Jane", 912)

    def test_update_student_service(self):
        self.student_service.add_student_service(100, "John", 911)
        self.student_service.update_student_service(100, "John", 912)
        updated_students = self.student_service.get_all_students()
        self.assertEqual(updated_students[10].get_name(), "John")
        self.assertEqual(updated_students[10].get_group(), 912)

    def test_remove_student_service(self):
        self.student_service.add_student_service(1, "John ", 919)
        self.assertEqual(len(self.student_service.get_all_students()), 11)
        self.student_service.remove_student_service(1)
        self.assertEqual(len(self.student_service.get_all_students()), 10)

    def tearDown(self) -> None:
        pass


class TestAssignmentService(TestCase):
    def setUp(self):
        self.assignment_repository = GenericRepository()
        self.assignment_service = AssignmentService(self.assignment_repository)

    def test_add_assignment_service(self):
        self.assignment_service.add_assignment_service(1, "Homework 1", 10)
        assignments = self.assignment_repository.find_all()
        self.assertEqual(len(assignments), 11)
        self.assertEqual(assignments[10].get_id(), 1)
        self.assertEqual(assignments[10].get_description(), "Homework 1")
        self.assertEqual(assignments[10].get_deadline(), 10)
        self.assertRaises(ValueError, self.assignment_service.add_assignment_service, 1, "Homework 2", 11)

    def test_update_assignment_service(self):
        self.assignment_service.add_assignment_service(1, "Homework 1", 10)
        self.assignment_service.update_assignment_service(1, "Homework 1", 11)
        updated_assignments = self.assignment_service.get_all_assignments()
        self.assertEqual(updated_assignments[10].get_description(), "Homework 1")
        self.assertEqual(updated_assignments[10].get_deadline(), 11)

    def test_remove_assignment_service(self):
        self.assignment_service.add_assignment_service(1, "Homework 1", 10)
        self.assertEqual(len(self.assignment_service.get_all_assignments()), 11)
        self.assignment_service.remove_assignment_service(1)
        self.assertEqual(len(self.assignment_service.get_all_assignments()), 10)

    def tearDown(self) -> None:
        pass
