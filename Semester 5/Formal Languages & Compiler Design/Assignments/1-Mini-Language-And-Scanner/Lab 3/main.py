from code_parser import CodeParser
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


def scan_files():
    scanner = CodeParser('problem1.txt', 'token.in')
    scanner.parse_file()

    # scanner = CodeParser('problem2.txt', 'token.in')
    # scanner.parse_file()
    #
    # scanner = CodeParser('problem3.txt', 'token.in')
    # scanner.parse_file()
    #
    # scanner = CodeParser('problem4(wrong).txt', 'token.in')
    # scanner.parse_file()


def main():
    print("Tests started...")
    run_tests()
    print("Tests passed!")
    print("Scanning files...")
    scan_files()
    print("Files scanned!")


if __name__ == "__main__":
    main()
