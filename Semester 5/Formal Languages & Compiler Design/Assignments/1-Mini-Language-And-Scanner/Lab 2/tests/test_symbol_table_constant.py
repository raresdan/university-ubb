import unittest
from models.symbol_tables import SymbolTableConstants


class TestSymbolTableConstants(unittest.TestCase):
    def __init__(self):
        self.constants = SymbolTableConstants()

    def test_symbol_table_constants(self):
        self.constants.add_constant(1, 777)
        assert (self.constants.get_constant(1)) == 777
        self.constants.add_constant(2, "python")
        assert (self.constants.get_constant(2)) == "python"
        self.constants.add_constant(3, 17)
        assert (self.constants.get_constant(3)) == 17
        self.constants.add_constant(4, "cpp")
        assert (self.constants.get_constant(4)) == "cpp"
        self.constants.add_constant(5, 1010)
        assert (self.constants.get_constant(5)) == 1010
        self.constants.add_constant(6, "oop")
        assert (self.constants.get_constant(6)) == "oop"
        self.constants.delete_constant(6)
        assert (self.constants.get_constant(6)) is None
