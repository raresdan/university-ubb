class Repository:
    def __init__(self):
        self.__all_entities = {}

    def find_all(self):
        return list(self.__all_entities.values())

    def find_by_id(self, entity_id):
        if entity_id in self.__all_entities:
            return self.__all_entities[entity_id]
        return None

    def add(self, entity):
        if self.find_by_id(entity.get_id()) is not None:
            raise ValueError("Duplicate ID!")
        self.__all_entities[entity.get_id()] = entity

    def update(self, entity):
        if self.find_by_id(entity.get_id()) is None:
            raise ValueError("Duplicate ID!")
        self.__all_entities[entity.get_id()] = entity
