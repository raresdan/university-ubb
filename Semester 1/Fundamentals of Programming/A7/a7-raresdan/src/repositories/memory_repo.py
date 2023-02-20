import copy


class GenericRepository:
    def __init__(self):
        self.__repository = []
        self.__history = []

    def return_all(self):
        return self.__repository

    def add_to_repository(self, expense):
        """
        adds an expense to repository
        :param expense: type Expense

        """
        if expense in self.__repository:
            raise ValueError("Expense already exists!")
        self.__history.append(self.__repository[:])
        self.__repository.append(expense)

    def length_of_repository(self):
        return len(self.__repository)

    def manipulate_expenses(self, new_list):
        # self.__history.append(self.__repository[:])
        self.__repository = copy.deepcopy(new_list)

    def filter_repository(self, value):
        self.__history.append(self.__repository[:])
        new_list = []
        for expense in self.__repository:
            amount = expense.get_amount()
            if int(amount) > int(value):
                new_list.append(expense)
        self.manipulate_expenses(new_list)
        return self.__repository

    def undo_repository(self):
        self.__repository[:] = self.__history[-1]
        self.__history.pop()
        return self.__repository
