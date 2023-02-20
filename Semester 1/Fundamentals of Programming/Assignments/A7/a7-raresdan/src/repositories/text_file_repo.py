from src.domain.domain import Expense
from src.repositories.memory_repo import GenericRepository


class TextFileRepository(GenericRepository):
    def __init__(self):
        super().__init__()
        self.__file_name = "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 1\\Fundamentals of Programming\\Assignments\\A7\\a7-raresdan\\src\\expenses"
        self.__load_data()

    def __load_data(self):
        with open(self.__file_name) as f:
            for line in f:
                line = line.strip()
                array = line.split(",")
                expense = Expense(int(array[0]), int(array[1]), array[2])
                super().add_to_repository(expense)

    def add_to_repository(self, expense):
        super().add_to_repository(expense)
        with open(self.__file_name, "a") as f:
            f.write(str(expense.get_day()) + "," + str(expense.get_amount()) + "," + str(expense.get_type()) + "\n")

    def filter_repository(self, expense):
        new_expenses = super().filter_repository(expense)
        with open(self.__file_name, "w") as f:
            for expense in new_expenses:
                f.write(str(expense.get_day()) + "," + str(expense.get_amount()) + "," + str(expense.get_type()) + "\n")

    def undo_repository(self):
        new_expenses = super().undo_repository()
        with open(self.__file_name, "w") as f:
            for expense in new_expenses:
                f.write(str(expense.get_day()) + "," + str(expense.get_amount()) + "," + str(expense.get_type()) + "\n")
