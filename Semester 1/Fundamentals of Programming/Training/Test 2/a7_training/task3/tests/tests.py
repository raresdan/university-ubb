from unittest import TestCase

from task3.domain.domain import Student
from task3.repository.repository import Repository
from task3.service.service import Service


class TestAdd(TestCase):
    def setUp(self) -> None:
        self.repository = Repository()
        self.service = Service(self.repository)

    def test_add_repository(self):
        student1 = Student(1, "John", 913)
        student2 = Student(1, "Jane", 913)
        length = len(self.repository.get_all())
        self.repository.add(student1)
        self.assertEqual(len(self.repository.get_all()), length + 1)
        self.assertRaises(ValueError, self.repository.add, student2)

    def test_add_service(self):
        length = len(self.service.return_all())
        self.service.add_service(1, "John", 913)
        self.assertEqual(len(self.service.return_all()), length + 1)
        self.assertRaises(ValueError, self.service.add_service, 1, "Jane", 913)

    def tearDown(self) -> None:
        pass
