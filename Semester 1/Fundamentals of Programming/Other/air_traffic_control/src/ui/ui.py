class Ui:
    def __init__(self, service):
        self.__service = service

    def display_all(self):
        flights = self.__service.return_all()
        index = 1
        for flight in flights:
            print(
                f"#{index} ID:{flight.get_id()}, Departure City: {flight.get_departure_city()}, Departure Time: {flight.get_departure_time()}, Arrival City: {flight.get_arrival_city()}, Arrival Time: {flight.get_arrival_time()}")
            index += 1

    def add(self):
        try:
            flight_id = input("Enter ID of the flight: ")
        except ValueError:
            print("Invalid input!")
            return
        try:
            d_city = input("Enter departure city of the flight: ")
        except ValueError:
            print("Invalid input!")
            return
        try:
            d_time = input("Enter departure time (HH:MM) of the flight: ")
        except ValueError:
            print("Invalid input!")
            return
        try:
            a_city = input("Enter arrival city of the flight: ")
        except ValueError:
            print("Invalid input!")
            return
        try:
            a_time = input("Enter arrival time (HH:MM) of the flight: ")
        except ValueError:
            print("Invalid input!")
            return
        try:
            self.__service.add_service(flight_id, d_city, d_time, a_city, a_time)
        except ValueError as ve:
            print(ve)

    def delete(self):
        try:
            flight_id = input("Enter ID of the flight you want to delete: ")
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            self.__service.delete_service(flight_id)
        except ValueError as ve:
            print(ve)

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
                self.add()
            elif option == 3:
                self.delete()
            elif option == 0:
                print("Menu exited!")
                break
            else:
                print("Invalid option!")
