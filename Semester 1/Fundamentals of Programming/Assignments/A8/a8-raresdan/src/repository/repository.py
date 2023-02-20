class GenericRepository:
    def __init__(self):
        self.__all_entities = {}

    def find_all(self):
        return list(self.__all_entities.values())

    def find_by_id(self, entity_id):
        """
        searches by id in the all entities dict
        :param entity_id: the entity's id which we want to find
        :return: the entity with a given id or None otherwise
        """
        if entity_id in self.__all_entities:
            return self.__all_entities[entity_id]
        return None

    def add(self, entity):
        """
        adds to the all entities dict
        :param entity: the entity which we want to add
        :return: adds the entity or raises ValueError if there already is an entity with that id
        """
        if self.find_by_id(entity.get_id()) is not None:
            raise ValueError("Duplicate ID! This ID already exists!")
        self.__all_entities[entity.get_id()] = entity

    def update(self, entity):
        """
        updates and entity
        :param entity: the entity which we want to update
        :return: updates the entity or raises ValueError if there doesn't exist an entity with that id
        """
        if self.find_by_id(entity.get_id()) is None:
            raise ValueError("Invalid ID! The ID does not exist!")
        self.__all_entities[entity.get_id()] = entity

    def remove_by_id(self, entity_id):
        """
        delete to the all entities dict
        :param entity_id: the entity's which we want to delete
        :return: deletes the entity or raises ValueError if there doesn't exist an entity with that id
        """
        if self.find_by_id(entity_id) is None:
            raise ValueError("Invalid ID! The ID does not exist!")
        del self.__all_entities[entity_id]
