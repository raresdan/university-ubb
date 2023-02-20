import random
from datetime import date

from task5.domain.activity import Activity


class ActivityService:
    def __init__(self, person_repository, activity_repository):
        self.__person_repository = person_repository
        self.__activity_repository = activity_repository
        self.generate_random()

    def return_all(self):
        return self.__activity_repository.get_all()

    def find_by_id_service(self):
        return self.__activity_repository.find_by_id()

    def add_service(self, activity_id, person_id, details):
        activity = Activity(activity_id, person_id, details)
        self.__activity_repository.add(activity)

    def update_service(self, activity_id, person_id, details):
        activity = Activity(activity_id, person_id, details)
        self.__activity_repository.update(activity)

    def remove_service(self, activity_id):
        self.__activity_repository.remove_by_id(activity_id)

    def generate_random(self):
        description = ["Party", "Park", "Restaurant", "Cabin", "Birthday"]
        person_ids = []
        persons = self.__person_repository.get_all()
        for person in persons:
            person_ids.append(person.get_id())
        while len(self.return_all()) < 10:
            try:
                self.add_service(random.randint(100, 999), random.choice(person_ids),
                                 [date(2023, random.randint(1, 12), random.randint(1, 31)), random.randint(1, 24),
                                  random.choice(description)])
            except ValueError:
                continue
