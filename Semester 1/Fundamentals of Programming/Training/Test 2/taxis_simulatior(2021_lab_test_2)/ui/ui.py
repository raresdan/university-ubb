class Ui:
    def __init__(self, service):
        self.__service = service

    @staticmethod
    def menu():
        print()
        print("----------------TAXI SIMULATOR----------------")
        print()
        print("1 - Show all existing taxis")
        print("2 - Add a custom ride")
        print("3 - Generate rides")
        print("0 - Exit app")

    def print_taxis(self):
        taxis = self.__service.get_all()
        taxis.sort(key=lambda k: k.get_fare(), reverse=True)
        i = 1
        for taxi in taxis:
            print(f"#{i} Id:{taxi.get_id()}".ljust(25, ' '),
                  f" Position:({taxi.get_x()},{taxi.get_y()}), Fare:{taxi.get_fare()}".rjust(25, ' '))

            i += 1

    def add_ride(self):
        try:
            starting_x = int(input("Enter starting x: "))
            if starting_x > 100 or starting_x < 0:
                print("Number must be between 0 and 100!")
                return
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            starting_y = int(input("Enter starting y: "))
            if starting_y > 100 or starting_y < 0:
                print("Number must be between 0 and 100!")
                return
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            ending_x = int(input("Enter ending x: "))
            if ending_x > 100 or ending_x < 0:
                print("Number must be between 0 and 100!")
                return
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            ending_y = int(input("Enter ending y: "))
            if ending_y > 100 or ending_y < 0:
                print("Number must be between 0 and 100!")
                return
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        ride, taxi = self.__service.add_ride(starting_x, starting_y, ending_x, ending_y)
        print()
        print(
            f"Taxi id:{ride.get_taxi_id()}, Start:({ride.get_starting_x()},{ride.get_starting_y()}), Finish:({ride.get_ending_x()},{ride.get_ending_y()})")
        print()

    def generate_rides(self):
        try:
            i = int(input("Number of rides to generate: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        rides, taxis = self.__service.generate_random_rides(i)
        i = 1
        for ride in rides:
            print(
                f"#{i} Taxi id:{ride.get_taxi_id()}, Start:({ride.get_starting_x()},{ride.get_starting_y()}), Finish:({ride.get_ending_x()},{ride.get_ending_y()})")
            print()
            i += 1

    def run_menu(self):
        self.menu()
        while True:
            while True:
                try:
                    print()
                    option = int(input("Enter option: "))
                    print()
                    break
                except ValueError as ve:
                    print("Invalid option", ve)
            if option == 1:
                self.print_taxis()
            elif option == 2:
                self.add_ride()
            elif option == 3:
                self.generate_rides()
            elif option == 0:
                print("App was exited successfully!")
                break
