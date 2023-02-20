from unittest import TestCase

from src.domain.entities import Student, Assignment


class TestStudent(TestCase):
    def setUp(self):
        self.student = Student(1, "John", 915)

    def test_get_id(self):
        self.assertEqual(self.student.get_id(), 1)

    def test_get_name(self):
        self.assertEqual(self.student.get_name(), "John")

    def test_get_group(self):
        self.assertEqual(self.student.get_group(), 915)

    def test_set_name(self):
        self.student.set_name("Jane")
        self.assertEqual(self.student.get_name(), "Jane")

    def test_set_group(self):
        self.student.set_group(917)
        self.assertEqual(self.student.get_group(), 917)

    def tearDown(self) -> None:
        pass


class TestAssignment(TestCase):
    def setUp(self):
        self.assignment = Assignment(1, "Homework 1", 20)

    def test_get_id(self):
        self.assertEqual(self.assignment.get_id(), 1)

    def test_get_description(self):
        self.assertEqual(self.assignment.get_description(), "Homework 1")

    def test_get_deadline(self):
        self.assertEqual(self.assignment.get_deadline(), 20)

    def test_set_description(self):
        self.assignment.set_description("Homework 2")
        self.assertEqual(self.assignment.get_description(), "Homework 2")

    def test_set_deadline(self):
        self.assignment.set_deadline(21)
        self.assertEqual(self.assignment.get_deadline(), 21)

    def tearDown(self) -> None:
        pass
