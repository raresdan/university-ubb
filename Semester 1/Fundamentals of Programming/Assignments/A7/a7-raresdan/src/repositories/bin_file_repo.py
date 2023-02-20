import os.path
import pickle

from src.repositories.memory_repo import GenericRepository


class BinFileRepository(GenericRepository):
    def __init__(self):
        super().__init__()
        self.__file_name = "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 1\\Fundamentals of Programming\\Assignments\\A7\\a7-raresdan\\src\\binary"
        self.__load_data()

    def __load_data(self):
        with open(self.__file_name, "rb") as f:
            if os.path.getsize(self.__file_name) > 0:
                expenses = pickle.load(f)
                for expense in expenses:
                    super().add_to_repository(expense)
                f.close()

    def add_to_repository(self, expense):
        super().add_to_repository(expense)
        with open(self.__file_name, "wb") as f:
            pickle.dump(self.return_all(), f)
            f.close()

    def filter_repository(self, expense):
        new_expenses = super().filter_repository(expense)
        with open(self.__file_name, "wb") as f:
            pickle.dump(new_expenses, f)
            self.__load_data()
            f.close()

    def undo_repository(self):
        new_expenses = super().undo_repository()
        with open(self.__file_name, "wb") as f:
            pickle.dump(new_expenses, f)
            self.__load_data()
            f.close()
