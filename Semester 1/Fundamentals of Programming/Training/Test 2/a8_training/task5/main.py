from task5.repository.repository import GenericRepository
from task5.service.activity_service import ActivityService
from task5.service.person_service import PersonService
from task5.ui.ui import Ui

if __name__ == "__main__":
    person_repository = GenericRepository()
    activity_repository = GenericRepository()
    person_service = PersonService(person_repository)
    activity_service = ActivityService(person_repository, activity_repository)
    ui = Ui(person_service, activity_service)
    ui.run_menu()
