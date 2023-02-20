from dataclasses import dataclass


@dataclass
class Person:
    person_id: int
    name: str
    phone: int

    def get_id(self):
        return self.person_id

    def get_name(self):
        return self.name

    def get_phone(self):
        return self.phone

    def set_name(self, new_name):
        self.name = new_name

    def set_phone(self, new_phone):
        self.phone = new_phone
