from tests.test_hash_table import TestHashTable
from tests.test_symbol_table_constant import TestSymbolTableConstants
from tests.test_symbol_tabel_identifier import TestSymbolTableIdentifiers


def run_tests():
    test_table = TestHashTable()
    test_table.test_hashtable()

    test_table = TestSymbolTableConstants()
    test_table.test_symbol_table_constants()

    test_table = TestSymbolTableIdentifiers()
    test_table.test_symbol_table_identifiers()


def main():
    print("Tests started...")
    run_tests()
    print("Tests passed!")


if __name__ == "__main__":
    main()
