from task1.src.repository.repository import Repository
from task1.src.service.service import Service
from task1.src.ui.ui import Ui

if __name__ == "__main__":
    repository = Repository()
    service = Service(repository)
    ui = Ui(service)
    ui.run_menu()
