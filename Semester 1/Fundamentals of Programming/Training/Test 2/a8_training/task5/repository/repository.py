class GenericRepository:
    def __init__(self):
        self.__all_entities = {}

    def get_all(self):
        return list(self.__all_entities.values())

    def check_value(self, value):
        valid = []
        for entity in list(self.__all_entities.items()):
            if value in entity:
                valid.append(entity)
        return valid

    def find_by_id(self, entity_id):
        if entity_id in self.__all_entities:
            return self.__all_entities[entity_id]
        return None

    def add(self, entity):
        if self.find_by_id(entity.get_id()) is not None:
            raise ValueError("Duplicate Id!")
        self.__all_entities[entity.get_id()] = entity

    def update(self, entity):
        if self.find_by_id(entity.get_id()) is None:
            raise ValueError("Nonexistent Id!")
        self.__all_entities[entity.get_id()] = entity

    def remove_by_id(self, entity_id):
        if self.find_by_id(entity_id) is None:
            raise ValueError("Nonexistent Id!")
        del self.__all_entities[entity_id]
