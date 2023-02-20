from task3.repository.repository import Repository
from task3.service.service import Service
from task3.ui.ui import Ui

if __name__ == "__main__":
    repository = Repository()
    service = Service(repository)
    ui = Ui(service)
    ui.run_menu()
