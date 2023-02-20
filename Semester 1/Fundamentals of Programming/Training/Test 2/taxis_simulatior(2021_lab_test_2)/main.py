from repository.repository import Repository
from service.service import Service
from ui.ui import Ui

if __name__ == "__main__":
    repository = Repository()
    while True:
        try:
            i = int(input("How many operational taxis do you want to work with? (Between 1 and 10): "))
            if 1 <= i <= 10:
                break
            else:
                print("Invalid input! Input must be between 1 and 10!")
        except ValueError as ve:
            print("Invalid input!", ve)
    service = Service(repository, i)
    ui = Ui(service)
    ui.run_menu()
