class Ui:
    def __init__(self, controller):
        self.__controller = controller

    def add_ui(self):
        try:
            fn = input("Enter family name: ")
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            g = int(input("Enter number of guests: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            ng = int(input("Enter room type: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            a = input("Enter arrival (DD.MM): ")
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            d = input("Enter departure (DD.MM): ")
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            self.__controller.add(fn, ng, a, d)
        except ValueError as ve:
            print(ve)

    def display_all(self):
        rooms = self.__controller.return_all()
        for room in rooms:
            print(
                f"ID:{room.get_id()}, Number:{room.get_room_number()}, Family Name:{room.get_family_name()}, Type: {room.get_guests()}, Arrival: {room.get_arrival()}, Departure: {room.get_departure()}")

    def run_menu(self):
        while True:
            while True:
                try:
                    print()
                    option = int(input("Enter your option: "))
                    print()
                    break
                except ValueError as ve:
                    print("Invalid option", ve)
            if option == 1:
                self.display_all()
            elif option == 2:
                self.add_ui()
            elif option == 0:
                print("Menu exited successfully!")
                break
            else:
                print("Invalid option")
