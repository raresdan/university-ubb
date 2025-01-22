import unittest
from models.symbol_tabel_identifiers import SymbolTableIdentifiers


class TestSymbolTableIdentifiers(unittest.TestCase):
    def __init__(self):
        self.constants = SymbolTableIdentifiers()

    def test_symbol_table_identifiers(self):
        self.constants.add_identifier("a", 777)
        assert (self.constants.get_identifier_value("a")) == 777
        self.constants.add_identifier("b", "python")
        assert (self.constants.get_identifier_value("b")) == "python"
        self.constants.add_identifier("c", 17)
        assert (self.constants.get_identifier_value("c")) == 17
        self.constants.add_identifier("d", "cpp")
        assert (self.constants.get_identifier_value("d")) == "cpp"
        self.constants.add_identifier("e", 1010)
        assert (self.constants.get_identifier_value("e")) == 1010
        self.constants.add_identifier("f", "oop")
        assert (self.constants.get_identifier_value("f")) == "oop"
        self.constants.delete_identifier("f")
        assert (self.constants.get_identifier_value("f")) is None