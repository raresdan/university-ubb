from src.repository.text_file_repository import TextFileRepository
from src.service.services import Service
from src.ui.ui import Ui

if __name__ == "__main__":
    repository = TextFileRepository()
    service = Service(repository)
    ui = Ui(service)
    ui.run_menu()
