from unittest import TestCase

from src.domain.grade import Grade
from src.repository.grade_repository import GradeRepository
from src.repository.repository import GenericRepository
from src.services.grade_service import GradeService


class TestGrade(TestCase):
    def setUp(self):
        self.grade = Grade(1, 2)

    def test_get_student_id(self):
        self.assertEqual(self.grade.get_student_id(), 1)

    def test_get_assignment_id(self):
        self.assertEqual(self.grade.get_assignment_id(), 2)

    def test_get_grade(self):
        self.assertEqual(self.grade.get_grade(), None)

    def test_set_grade(self):
        self.grade.set_grade(10)
        self.assertEqual(self.grade.get_grade(), 10)

    def tearDown(self) -> None:
        pass


class TestGradeRepository(TestCase):
    def setUp(self):
        self.grade_repository = GradeRepository()
        self.grade1 = Grade(1, 1)
        self.grade2 = Grade(2, 2)
        self.grade3 = Grade(3, 3)

    def test_add_grade(self):
        self.grade_repository.add(self.grade1)
        self.assertEqual(len(self.grade_repository.find_all()), 1)
        self.grade_repository.add(self.grade2)
        self.assertEqual(len(self.grade_repository.find_all()), 2)
        self.assertRaises(ValueError, self.grade_repository.add, self.grade1)

    def test_update_grade(self):
        self.grade_repository.add(self.grade1)
        self.grade_repository.update(Grade(1, 1, 10))
        self.assertEqual(self.grade_repository.find_by_student_id(1)[0].get_grade(), 10)
        self.assertEqual(self.grade_repository.find_by_assignment_id(1)[0].get_grade(), 10)
        self.assertRaises(ValueError, self.grade_repository.update, Grade(5, 5))

    def test_remove_grade(self):
        self.grade_repository.add(self.grade1)
        self.grade_repository.add(self.grade2)
        self.grade_repository.remove_by_student_id(1)
        self.assertEqual(len(self.grade_repository.find_all()), 1)
        self.grade_repository.remove_by_assignment_id(2)
        self.assertEqual(len(self.grade_repository.find_all()), 0)
        self.assertRaises(ValueError, self.grade_repository.remove_by_student_id, 5)
        self.assertRaises(ValueError, self.grade_repository.remove_by_assignment_id, 5)

    def tearDown(self) -> None:
        pass


class TestGradeService(TestCase):
    def setUp(self):
        self.grade_repository = GradeRepository()
        self.student_repository = GenericRepository()
        self.assignment_repository = GenericRepository()
        self.grade_service = GradeService(self.grade_repository, self.student_repository, self.assignment_repository)

    def test_add_grade_service(self):
        self.grade_service.add_grade_service(1, 2, None)
        assignments = self.grade_repository.find_all()
        self.assertEqual(len(assignments), 1)
        self.assertEqual(assignments[0].get_student_id(), 1)
        self.assertEqual(assignments[0].get_assignment_id(), 2)
        self.assertEqual(assignments[0].get_grade(), None)
        self.assertRaises(ValueError, self.grade_service.add_grade_service, 1, 2, 9)

    def test_update_grade_service(self):
        self.grade_service.add_grade_service(1, 2, None)
        self.grade_service.update_grade_service(1, 2, 9)
        updated_grades = self.grade_service.get_all_grades()
        self.assertEqual(updated_grades[0].get_grade(), 9)

    def test_remove_grade_service(self):
        self.grade_service.add_grade_service(1, 2, None)
        self.assertEqual(len(self.grade_service.get_all_grades()), 1)
        self.grade_service.remove_grade_by_student_id(1)
        self.assertEqual(len(self.grade_service.get_all_grades()), 0)
        self.grade_service.add_grade_service(1, 2, None)
        self.assertEqual(len(self.grade_service.get_all_grades()), 1)
        self.grade_service.remove_grade_by_assignment_id(2)
        self.assertEqual(len(self.grade_service.get_all_grades()), 0)

    def tearDown(self) -> None:
        pass
