import configparser

from src.repositories.bin_file_repo import BinFileRepository
from src.repositories.memory_repo import GenericRepository
from src.repositories.text_file_repo import TextFileRepository
from src.services.services import Services
from src.ui.ui import Ui

if __name__ == "__main__":
    config = configparser.RawConfigParser()
    config.read("settings.properties")
    if config.get("repository_section", "repo") == "memory":
        repository = GenericRepository()
    if config.get("repository_section", "repo") == "binary":
        repository = BinFileRepository()
    if config.get("repository_section", "repo") == "text":
        repository = TextFileRepository()

    expenses_service = Services(repository, config)
    console = Ui(expenses_service)
    console.run_menu()
