from models.hash_table import HashTable


class SymbolTableConstants:
    def __init__(self):
        self.symboltable = HashTable()

    def add_constant(self, identifier, value):
        self.symboltable.add(identifier, value)

    def get_constant(self, identifier):
        return self.symboltable.get(identifier)

    def delete_constant(self, identifier):
        return self.symboltable.pop(identifier)
