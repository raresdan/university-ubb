class Ui:

    def __init__(self, service):
        self.__service = service

    @staticmethod
    def menu():
        print("----------------Menu----------------")
        print("add - Add an expense. Expense data is read from the console.")
        print("list - Display the list of expenses.")
        print("filter - Filter the list so that it contains only expenses above a certain value read from the console.")
        print("undo - Undo the last operation that modified program data. This step can be repeated.")
        print("exit - Exit the menu")

    def add_expense(self):
        day = input("Enter the day of the expense: ")
        try:
            day = int(day)
        except ValueError:
            print("Invalid day input! Day must be integer!")
            return
        if day < 1 or day > 30:
            print("Invalid day input! Not between 1 and 30!")
            return
        amount = input("Enter the amount of the expense: ")
        try:
            amount = int(amount)
        except ValueError:
            print("Invalid amount input! Amount must be integer!")
            return
        if amount < 0:
            print("Invalid amount input! Amount has to be positive!")
            return
        ttype = input("Enter the type of the expense: ")
        self.__service.add_expense_service(day, amount, ttype)

    def add_random_to_repository(self):
        self.__service.generate_10()

    def filter_expense(self):
        value = input("Enter a value: ")
        self.__service.filter_expenses_service(value)

    def list_expenses(self):
        mylist = self.__service.get_all_service()
        index = 1
        for expense in mylist:
            print(f"#{index} {expense}")
            index = index + 1

    def undo(self):
        try:
            self.__service.undo_service()
            print("The last operation was undone!")
        except IndexError:
            print("No operation left to be undone!")
        except Exception as e:
            print(f"Exception: {e}!")

    def run_menu(self):
        Ui.menu()
        while True:
            while True:
                try:
                    print()
                    option = input("Enter the command corresponding to the desired action: ")
                    print()
                    break
                except ValueError:
                    print("Invalid command!")
            if option.lower() == "add":
                self.add_expense()
            elif option.lower() == "list":
                self.list_expenses()
            elif option.lower() == "filter":
                self.filter_expense()
            elif option.lower() == "undo":
                self.undo()
            elif option.lower() == "exit":
                print("The menu was exited successfully!")
                break
            else:
                print("Invalid command!")
                print()
