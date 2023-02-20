class Repository:
    def __init__(self):
        self.__all_entities = {}

    def get_all(self):
        return list(self.__all_entities.values())

    def find_by_id(self, entity_id):
        if entity_id in self.__all_entities:
            return self.__all_entities[entity_id]
        return None

    def add(self, entity):
        if self.find_by_id(entity.get_id()) is not None:
            raise ValueError("Duplicate Id!")
        self.__all_entities[entity.get_id()] = entity
