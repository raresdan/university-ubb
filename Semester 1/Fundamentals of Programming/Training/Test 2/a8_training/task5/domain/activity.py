from dataclasses import dataclass


@dataclass
class Activity:
    activity_id: int
    person_id: int
    details: list

    def get_id(self):
        return self.activity_id

    def get_person_id(self):
        return self.person_id

    def get_details(self):
        return self.details

    def set_details(self, new_list):
        self.details = new_list
