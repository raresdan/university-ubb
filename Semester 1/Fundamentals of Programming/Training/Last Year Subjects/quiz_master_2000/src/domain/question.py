from dataclasses import dataclass


@dataclass
class Question:
    __id: int
    __text: str
    __choice_a: str
    __choice_b: str
    __choice_c: str
    __correct_choice: str
    __difficulty: str

    def get_id(self):
        return self.__id

    def get_text(self):
        return self.__text

    def get_choice_a(self):
        return self.__choice_a

    def get_choice_b(self):
        return self.__choice_b

    def get_choice_c(self):
        return self.__choice_c

    def get_correct_choice(self):
        return self.__correct_choice

    def get_difficulty(self):
        return self.__difficulty