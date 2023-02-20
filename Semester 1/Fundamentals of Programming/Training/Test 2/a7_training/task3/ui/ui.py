class Ui:
    def __init__(self, service):
        self.__service = service

    @staticmethod
    def menu():
        print("1 - display all")
        print("2 - add student")
        print("3 - delete students from a certain group")
        print("0 - exit")

    def print_all(self):
        students = self.__service.return_all()
        index = 1
        for student in students:
            print(f"#{index}, Id: {student.get_id()}, Name: {student.get_name()}, Group: {student.get_group()}")
            index += 1

    def add_student(self):
        try:
            student_id = int(input("Enter student's id: "))
        except ValueError as ve:
            print("Id must be a unique integer!", ve)
            return
        try:
            name = input("Enter student's name: ")
        except ValueError as ve:
            print("Invalid student name!", ve)
            return
        try:
            group = int(input("Enter student's group: "))
        except ValueError as ve:
            print("Invalid group!", ve)
            return
        try:
            self.__service.add_service(student_id, name, group)
        except ValueError as ve:
            print(ve)

    def filter_by_group(self):
        try:
            group = int(input("Enter student's group: "))
        except ValueError as ve:
            print("Invalid group!", ve)
            return
        try:
            self.__service.remove_by_group(group)
        except ValueError as ve:
            print(ve)

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
                self.print_all()
            elif option == 2:
                self.add_student()
            elif option == 3:
                self.filter_by_group()
            elif option == 0:
                break
            else:
                print("Invalid option!")
