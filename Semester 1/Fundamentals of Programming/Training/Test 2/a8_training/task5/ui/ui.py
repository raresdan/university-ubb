from datetime import date


class Ui:
    def __init__(self, person_service, activity_service):
        self.__person_service = person_service
        self.__activity_service = activity_service

    def display_person(self):
        persons = self.__person_service.return_all()
        for person in persons:
            print(f"Id: {person.get_id()}, Name: {person.get_name()}, Phone: {person.get_phone()}")

    def display_activities(self):
        activities = self.__activity_service.return_all()
        for activity in activities:
            print(
                f"Activity Id: {activity.get_id()}, Person Id: {activity.get_person_id()}, Date:{activity.get_details()[0]}, Time: {activity.get_details()[1]}:00, Description: {activity.get_details()[2]}")

    def add_person(self):
        try:
            person_id = int(input("Enter person id: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            name = input("Enter name: ")
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            phone = int(input("Enter phone number: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            self.__person_service.add_service(person_id, name, phone)
        except ValueError as ve:
            print(ve)

    def add_activity(self):
        try:
            activity_id = int(input("Enter activity id: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            person_id = int(input("Enter person id: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            month = int(input("Enter month: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            day = int(input("Enter day: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            time = int(input("Enter time: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            description = input("Enter description: ")
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            self.__activity_service.add_service(activity_id, person_id, [date(2023, month, day), time, description])
        except ValueError as ve:
            print(ve)

    def update_person(self):
        try:
            person_id = int(input("Enter person id: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            name = input("Enter new name: ")
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            phone = int(input("Enter new phone number: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            self.__person_service.update_service(person_id, name, phone)
        except ValueError as ve:
            print(ve)

    def update_activity(self):
        try:
            activity_id = int(input("Enter activity id: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            person_id = int(input("Enter person id: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            month = int(input("Enter new month: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            day = int(input("Enter new day: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            time = int(input("Enter new time: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            description = input("Enter new description: ")
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            self.__activity_service.update_service(activity_id, person_id, [date(2023, month, day), time, description])
        except ValueError as ve:
            print(ve)

    def remove_person(self):
        try:
            person_id = int(input("Enter person id: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            self.__person_service.remove_service(person_id)
        except ValueError as ve:
            print(ve)

    def remove_activity(self):
        try:
            activity_id = int(input("Enter activity id: "))
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            self.__activity_service.remove_service(activity_id)
        except ValueError as ve:
            print(ve)

    def search_person(self):
        try:
            search = input("🔎: ")
        except ValueError as ve:
            print("Invalid input!", ve)
            return
        try:
            self.__person_service.find_by_id_service(search)
        except ValueError as ve:
            print(ve)
        persons = self.__person_service.check_service(search)
        for person in persons:
            print(f"Id: {person.get_id()}, Name: {person.get_name()}, Phone: {person.get_phone()}")

    def run_menu(self):
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
                self.display_person()
            elif option == 2:
                self.add_person()
            elif option == 3:
                self.update_person()
            elif option == 4:
                self.remove_person()
            elif option == 5:
                self.search_person()
            elif option == 6:
                self.display_activities()
            elif option == 7:
                self.add_activity()
            elif option == 8:
                self.update_activity()
            elif option == 9:
                self.remove_activity()
            elif option == 0:
                print("App exited successfully!")
                break
            else:
                print("Invalid option!")
