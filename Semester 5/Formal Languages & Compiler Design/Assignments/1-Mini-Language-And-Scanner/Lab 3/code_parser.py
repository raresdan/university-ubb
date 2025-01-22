from models.symbol_tabel_identifiers import SymbolTableIdentifiers
from models.symbol_table_constants import SymbolTableConstants
import re


class CodeParser:
    IDENTIFIER = 0
    CONSTANT = 1
    OPERATORS = 2
    RESERVED_WORDS = 3
    SEPARATORS = 4

    def __init__(self, filename, token_file):
        self.filename = filename
        self.token_file = token_file
        self.constant_table = SymbolTableConstants()
        self.identifiers_table = SymbolTableIdentifiers()
        self.pif = []
        self.constants_count = 0
        self.tokens = {"reserved_words": {}, "operators": {}, "separators": {}}
        self._load_tokens()

    def parse_file(self):
        with open(self.filename, 'r') as program:
            for line_count, line in enumerate(program, 1):
                tokens_in_line = re.split(r'(\b\w+\b'r'|[=<>!+\-*/]=?'r'|[(){}\[\]\'";,.:]'r')', line.strip())
                for token in filter(None, map(str.strip, tokens_in_line)):
                    if self._process_constant(token) or self._process_reserved_operator_separator(
                            token) or self._process_identifier(token):
                        continue
                    print(f'Lexical error at line {line_count}; Token {token} is invalid!')
                    return
            print('Lexically correct')
        self._write_output()

    def _load_tokens(self):
        section = None
        with open(self.token_file, 'r') as file:
            for line_no, line in enumerate(file, 2):
                line = line.strip()
                if line in ['[reserved_words]', '[operators]', '[separators]']:
                    section = line.strip('[]')
                    continue
                if section:
                    self.tokens[section][line] = line_no

    def _process_constant(self, token):
        is_string_constant = (token.startswith('"') and token.endswith('"')) or (
                token.startswith("'") and token.endswith("'"))
        if is_string_constant:
            token = token.strip('"\'').replace(' ', '')
        else:
            if token.isdigit():
                if len(token) > 1 and token[0] == '0':
                    return False
            else:
                return False
        if self.constant_table.get_constant(token) is None:
            self.constant_table.add_constant(token, self.constants_count)
            self.pif.append((self.CONSTANT, self.constants_count))
            self.constants_count += 1
        return True

    def _process_reserved_operator_separator(self, token):
        for token_type, token_dict in self.tokens.items():
            if token in token_dict:
                token_type_value = getattr(self, token_type.upper())
                self.pif.append((token_type_value, token_dict[token]))
                return True
        return False

    def _process_identifier(self, token):
        if token[0].isalpha() or token[0] == '_':
            if all(c.isalnum() or c == '_' for c in token[1:]):
                if self.identifiers_table.get_identifier_value(token) is None:
                    self.identifiers_table.add_identifier(token, None)
                self.pif.append((self.IDENTIFIER, self.identifiers_table.get_identifier_value(token)))
                return True
        return False

    def _write_output(self):
        with open('ST.out', 'w') as output:
            output.write(f"Identifiers: {self.identifiers_table.symboltable}\n")
            output.write(f"Constants: {self.constant_table.symboltable}\n")

        with open('PIF.out', 'w') as output:
            for token_type, position in self.pif:
                output.write(f"{token_type} - {position}\n")
