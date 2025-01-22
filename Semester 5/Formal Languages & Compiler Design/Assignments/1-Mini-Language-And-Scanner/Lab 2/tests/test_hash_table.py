import unittest
from models.hash_table import HashTable


class TestHashTable(unittest.TestCase):
    def __init__(self):
        self.table = HashTable()

    def test_hashtable(self):
        self.table.add("a", 1)
        assert (self.table.get("a")) == 1
        self.table.add("b", 2)
        assert (self.table.get("b")) == 2
        self.table.add("c", 3)
        assert (self.table.get("c")) == 3
        self.table.add("d", 4)
        assert (self.table.get("d")) == 4
        self.table.add("e", 4)
        assert (self.table.get("e")) == 4
