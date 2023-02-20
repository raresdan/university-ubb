import unittest

from src.repository.grade_repository import GradeRepository
from src.repository.repository import GenericRepository
from src.services.grade_service import GradeService
from src.services.service import StudentService, AssignmentService
from src.ui.ui import Ui

if __name__ == "__main__":
    students_repository = GenericRepository()
    assignments_repository = GenericRepository()
    grades_repository = GradeRepository()

    students_service = StudentService(students_repository)
    assignments_service = AssignmentService(assignments_repository)
    grades_service = GradeService(grades_repository, students_repository, assignments_repository)

    console = Ui(students_service, assignments_service, grades_service)
    unittest.TestCase()
    console.run_menu()
