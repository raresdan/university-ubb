"""
Manage a list of expenses. Each expense has a
day (integer between 1 and 30),
amount of money (positive integer)
and expense type (string).
Provide the following features:

1. Add an expense. Expense data is read from the console.
2. Display the list of expenses.
3. Filter the list so that it contains only expenses above a certain value read from the console.
4. Undo the last operation that modified program data. This step can be repeated.
The user can undo only those operations made during the current run of the program.
"""
import random


class Expense:

    def __init__(self, day, amount, ttype):
        if int(day) < 1 or int(day) > 30:
            raise ValueError("Invalid day! Not between 1 and 30!")
        if int(amount) < 1:
            raise ValueError("Invalid amount! Amount must be positive!")
        self.__day = day
        self.__amount = amount
        self.__type = ttype

    def __str__(self):
        return f"Day: {self.__day}, Amount: {self.__amount}, Type: {self.__type}"

    def __repr__(self):
        return f"Day: {self.__day}, Amount: {self.__amount}, Type: {self.__type}"

    def get_day(self):
        return self.__day

    def get_amount(self):
        return self.__amount

    def get_type(self):
        return self.__type

    def set_day(self, day):
        k = 1
        try:
            if int(day) > 30 or int(day) < 1:
                k = 0
        except ValueError:
            k = 0
        if k == 0:
            raise ValueError("Expense's day should be an integer between 1 and 30!")
        self.__day = day

    def set_amount(self, amount):
        k = 1
        try:
            if int(amount) < 0:
                k = 0
        except ValueError:
            k = 0
        if k == 0:
            raise ValueError("Expense's amount should be a positive integer!")
        self.__amount = amount

    def set_type(self, ttype):
        try:
            ttype = int(ttype)
            k = 0
        except ValueError:
            k = 1
        if k == 1:
            if len(ttype) == 0:
                k = 0
        if k == 0:
            raise ValueError("Expense's type should be a string!")
        self.__type = ttype

    def are_equal(self, expense):
        return self.__day == expense.__day and self.__amount == expense.__amount and self.__type and expense.__type



