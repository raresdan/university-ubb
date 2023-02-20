from task1.src.domain.domain import Complex


class Repository:
    def __init__(self):
        self.__all_complex = []
        self.__history = []

    def get_all(self):
        return self.__all_complex

    def add(self, complex):
        if complex in self.__all_complex:
            raise ValueError("Duplicate")
        self.__history.append(self.__all_complex[:])
        self.__all_complex.append(complex)

    def remove(self, complex):
        if complex not in self.__all_complex:
            raise ValueError("Nonexistent number")
        self.__history.append(self.__all_complex[:])
        self.__all_complex.remove(complex)

    def manipulate_list(self, new_list):
        self.__history.append(self.__all_complex[:])
        self.__all_complex = new_list

    def undo(self):
        self.__all_complex[:] = self.__history[-1]
        self.__history.pop()
        return self.__all_complex
