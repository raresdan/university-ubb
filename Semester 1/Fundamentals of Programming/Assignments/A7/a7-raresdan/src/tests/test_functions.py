import configparser
from unittest import TestCase

from src.repositories.bin_file_repo import BinFileRepository
from src.repositories.memory_repo import GenericRepository
from src.repositories.text_file_repo import TextFileRepository
from src.services.services import Services


class TestMemory(TestCase):
    def setUp(self):
        self.__repository = GenericRepository()
        self.__config = configparser.RawConfigParser()
        self.__config.read(
            "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 1\\Fundamentals of Programming\\Assignments\\A7\\a7-raresdan\\src\\settings.properties")
        self.__service = Services(self.__repository, self.__config)

    def test_add(self):
        expense_list = self.__service.get_all_service()
        initial_length = len(expense_list)
        self.__service.add_expense_service(12, 300, "Gas")
        expense_list = self.__service.get_all_service()
        self.assertEqual(len(expense_list), initial_length+1)

    def tearDown(self):

        pass


class TestText(TestCase):
    def setUp(self):
        self.__config = configparser.RawConfigParser()
        self.__config.read(
            "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 1\\Fundamentals of Programming\\Assignments\\A7\\a7-raresdan\\src\\settings.properties")
        self.__repository = TextFileRepository()
        self.__service = Services(self.__repository, self.__config)

    def test_add(self):
        expense_list = self.__service.get_all_service()
        initial_length = len(expense_list)
        self.__service.add_expense_service(12, 300, "Gas")
        expense_list = self.__service.get_all_service()
        self.assertEqual(len(expense_list), initial_length + 1)

    def tearDown(self):
        pass


class TestBinary(TestCase):
    def setUp(self):
        self.__config = configparser.RawConfigParser()
        self.__config.read(
            "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 1\\Fundamentals of Programming\\Assignments\\A7\\a7-raresdan\\src\\settings.properties")
        self.__repository = BinFileRepository()
        self.__service = Services(self.__repository, self.__config)

    def test_add(self):
        expense_list = self.__service.get_all_service()
        initial_length = len(expense_list)
        self.__service.add_expense_service(12, 300, "Gas")
        expense_list = self.__service.get_all_service()
        self.assertEqual(len(expense_list), initial_length + 1)

    def tearDown(self):
        pass
