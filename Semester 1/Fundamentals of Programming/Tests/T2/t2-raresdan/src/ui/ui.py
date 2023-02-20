class Ui:
    def __init__(self, service):
        self.__service = service

    @staticmethod
    def menu():
        print("--------------MENU--------------")
        print("1 - add an address")
        print("2 - display all addresses")
        print("3 - show addresses closest to (x,y)")
        print("4 - show new taxi station placement")
        print("0 - exit")

    def add_address(self):
        try:
            address_id = int(input("Enter address id: "))
            if address_id < 0:
                print("Id must be positive!")
                return
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            name = input("Enter address name: ")
            if len(name) < 3:
                print("Name should have at least 3 characters!")
                return
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            number = int(input("Enter address number: "))
            if number > 100 or number < 0:
                print("Number should be positive, at most 100!")
                return
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            x = int(input("Enter address coordinate x: "))
            if x > 100 or x < -100:
                print("Coordinates must be between -100 and 100!")
                return
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            y = int(input("Enter address coordinate y: "))
            if y > 100 or y < -100:
                print("Coordinates must be between -100 and 100!")
                return
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            self.__service.add_service(address_id, name, number, x, y)
        except ValueError as ve:
            print(ve)

    def display_all(self):
        addresses = self.__service.return_all()
        index = 1
        for address in addresses:
            print(
                f"#{index} Address ID: {address.get_id()} Name: {address.get_name()} Number: {address.get_number()} Coordinates:({address.get_x()},{address.get_y()})")
            index += 1

    def taxi_stations(self):
        try:
            x = int(input("Enter address coordinate x: "))
            if x > 100 or x < -100:
                print("Coordinates must be between -100 and 100!")
                return
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            y = int(input("Enter address coordinate y: "))
            if y > 100 or y < -100:
                print("Coordinates must be between -100 and 100!")
                return
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            d = int(input("Enter distance: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            self.__service.stations(x, y, d)
        except ValueError as ve:
            print(ve)
            return
        addresses, distances = self.__service.stations(x, y, d)
        for i in range(len(addresses)):
            print(
                f"Address ID: {addresses[i].get_id()} Name: {addresses[i].get_name()} Number: {addresses[i].get_number()} Coordinates:({addresses[i].get_y()},{addresses[i].get_y()}) , Distance:{distances[i]}")

    def optimal_position(self):
        final_x, final_y = self.__service.minimum_distance()
        print(f"The new taxi stations should be placed at: ({final_x},{final_y})")

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
                self.add_address()
            elif option == 2:
                self.display_all()
            elif option == 3:
                self.taxi_stations()
            elif option == 4:
                self.optimal_position()
            elif option == 0:
                print("App exited successfully!")
                break
            else:
                print("Invalid option!")
