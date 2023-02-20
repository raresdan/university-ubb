from unittest import TestCase

from task1.src.domain.domain import Complex
from task1.src.repository.repository import Repository
from task1.src.service.service import Service


class TestAdd(TestCase):
    def setUp(self) -> None:
        self.repository = Repository()
        self.service = Service(self.repository)

    def test_add(self):
        number = Complex(1, 2)
        length = len(self.repository.get_all())
        self.repository.add(number)
        self.assertEqual(len(self.repository.get_all()), length + 1)
        length = len(self.repository.get_all())
        self.service.add_service(1, 1)
        self.assertEqual(len(self.repository.get_all()), length + 1)
        self.assertRaises(ValueError, self.service.add_service, 1, 2)

    def tearDown(self) -> None:
        pass
