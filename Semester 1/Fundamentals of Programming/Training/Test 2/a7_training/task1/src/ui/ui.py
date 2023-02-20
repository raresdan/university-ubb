class Ui:
    def __init__(self, service):
        self.__service = service

    @staticmethod
    def menu():
        print("1 - display all")
        print("2 - add number")
        print("3 - filter between 2 indexes")
        print("4 - undo")
        print("0 - exit")

    def display_all(self):
        numbers = self.__service.return_all()
        index = 1
        for number in numbers:
            a = number.get_real()
            b = number.get_imaginary()
            if a > 0:
                a = str(a)
            elif a == 0:
                a = ''
            if b > 0:
                b = "+" + str(b)
            elif b == 0:
                b = ''
            print(f"#{index} {a}{b}i")
            index += 1

    def add_complex(self):
        try:
            real = int(input("Enter real part:"))
        except ValueError:
            print("Real part must be integer!")
            return
        try:
            imaginary = int(input("Enter imaginary part:"))
        except ValueError:
            print("Imaginary part must be integer!")
            return
        self.__service.add_service(real, imaginary)

    def filter_numbers(self):
        try:
            start = int(input("Enter the starting index:"))
        except ValueError:
            print("Index must be integer!")
            return
        try:
            end = int(input("Enter the ending index:"))
        except ValueError:
            print("Index must be integer!")
            return
        self.__service.filter(start, end)

    def undo(self):
        try:
            self.__service.undo_service()
            print("The last operation was undone!")
        except IndexError:
            print("No operation left to be undone!")
        except Exception as e:
            print(f"Exception: {e}!")

    def run_menu(self):
        self.menu()
        while True:
            while True:
                try:
                    print()
                    option = int(input("Enter your option: "))
                    print()
                    break
                except ValueError as ve:
                    print("Invalid option!", ve)
            if option == 1:
                self.display_all()
            elif option == 2:
                self.add_complex()
            elif option == 3:
                self.filter_numbers()
            elif option == 4:
                self.undo()
            elif option == 0:
                break
            else:
                print("Invalid option!")
