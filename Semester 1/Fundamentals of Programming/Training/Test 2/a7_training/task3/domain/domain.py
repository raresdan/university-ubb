from dataclasses import dataclass


@dataclass
class Student:
    id: int
    name: str
    group: int

    def get_id(self):
        return self.id

    def get_name(self):
        return self.name

    def get_group(self):
        return self.group

    def set_id(self, new_id):
        self.id = new_id

    def set_name(self, new_name):
        self.name = new_name

    def set_group(self, new_group):
        self.group = new_group
