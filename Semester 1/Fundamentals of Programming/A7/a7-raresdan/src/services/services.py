import os.path
import random

from src.domain.domain import Expense


class Services:

    def __init__(self, expenses_repository, config):
        self.__expenses_repository = expenses_repository
        self.__config = config
        if self.__config.get("repository_section", "repo") == "memory":
            self.generate_10()
        if self.__config.get("repository_section", "repo") == "binary":
            if os.path.getsize(
                    "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 1\\Fundamentals of Programming\\Assignments\\A7\\a7-raresdan\\src\\binary") < 1:
                self.generate_10()
        if self.__config.get("repository_section", "repo") == "text":
            if os.path.getsize(
                    "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 1\\Fundamentals of Programming\\Assignments\\A7\\a7-raresdan\\src\\expenses") < 1:
                self.generate_10()

    def add_expense_service(self, day: int, amount: int, ttype: str):
        """

        :param day: between 1 and 30
        :param amount: integer
        :param ttype: string
        :return: adds an expense to the list of expenses
        """
        expense = Expense(day, amount, ttype)
        self.__expenses_repository.add_to_repository(expense)

    def filter_expenses_service(self, value):
        self.__expenses_repository.filter_repository(int(value))

    def get_all_service(self):
        return self.__expenses_repository.return_all()

    def generate_10(self):
        for _ in range(10):
            types = ["Food", "Shopping", "Bill", "Home", "Other", "Family", "Event", "Rent", "Gift", "Taxes"]
            expense = Expense(random.randint(1, 30), random.randint(50, 1000), random.choice(types))
            self.__expenses_repository.add_to_repository(expense)

    def undo_service(self):
        return self.__expenses_repository.undo_repository()
