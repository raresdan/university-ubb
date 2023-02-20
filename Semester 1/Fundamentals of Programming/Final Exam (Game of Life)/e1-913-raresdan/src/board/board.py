import copy

import texttable


class Board:
    def __init__(self):
        self.__data = [[" " for _ in range(8)] for _ in range(8)]

    def __str__(self):
        board = texttable.Texttable()
        for i in range(8):
            row = []
            for j in range(8):
                row.append(self.__data[i][j])
            board.add_row(row)
        return board.draw()

    def advancing(self):
        """
        The function checks for the neighbors of each cell and:
            * any live cell with fewer than 2 live neighbors dies
            * any live cell with 2 or 3 neighbors lives
            * any live cell with more than 3 live neighbors dies
            * any dead cell with exactly 3 neighbours become alive
        It uses a copy of the data such that, if one "alive" square is deleted the configuration might be
        generated wrong
        :return: Changes the self.__data values accordingly
        """
        data_copy = copy.deepcopy(self.__data)
        for i in range(8):
            for j in range(8):
                neighbors = self.check_neighbours(i, j)
                if self.__data[i][j] == "X":
                    if neighbors < 2:
                        data_copy[i][j] = " "
                    if neighbors > 3:
                        data_copy[i][j] = " "
                if self.__data[i][j] == " ":
                    if neighbors == 3:
                        data_copy[i][j] = "X"
        self.__data = copy.deepcopy(data_copy)

    def check_neighbours(self, i, j):
        counter = 0
        if 0 <= i < 8 and 0 <= j + 1 < 8:
            if self.__data[i][j + 1] == "X":
                counter += 1
        if 0 <= i + 1 < 8 and 0 <= j + 1 < 8:
            if self.__data[i + 1][j + 1] == "X":
                counter += 1
        if 0 <= i + 1 < 8 and 0 <= j < 8:
            if self.__data[i + 1][j] == "X":
                counter += 1
        if 0 <= i + 1 < 8 and j - 1 >= 0 and j < 8:
            if self.__data[i + 1][j - 1] == "X":
                counter += 1
        if 0 <= i < 8 and j - 1 >= 0 and j < 8:
            if self.__data[i][j - 1] == "X":
                counter += 1
        if 0 <= i - 1 < 8 and j - 1 >= 0 and j < 8:
            if self.__data[i - 1][j - 1] == "X":
                counter += 1
        if 0 <= i - 1 < 8 and 0 <= j < 8:
            if self.__data[i - 1][j] == "X":
                counter += 1
        if 0 <= i - 1 < 8 and 0 <= j + 1 < 8:
            if self.__data[i - 1][j + 1] == "X":
                counter += 1
        return counter

    def place_block(self, i, j):
        x = i - 1
        y = j - 1
        if 1 <= i <= 7 >= j >= 1:
            if self.__data[x][y] == "X" or self.__data[x][y + 1] == "X" or self.__data[x + 1][y + 1] == "X" or \
                    self.__data[x + 1][y] == "X":
                raise ValueError("occupied!")
        else:
            raise ValueError("outside!")
        self.__data[x][y] = "X"
        self.__data[x][y + 1] = "X"
        self.__data[x + 1][y + 1] = "X"
        self.__data[x + 1][y] = "X"

    def place_tub(self, i, j):

        x = i - 1
        y = j - 1
        if 1 <= i <= 7 >= j >= 2:
            if self.__data[x][y] == "X" or self.__data[x + 1][y + 1] == "X" or self.__data[x + 2][y] == "X" or \
                    self.__data[x + 1][y - 1] == "X":
                raise ValueError("occupied")
        else:
            raise ValueError("outside!")
        self.__data[x][y] = "X"
        self.__data[x + 1][y + 1] = "X"
        self.__data[x + 2][y] = "X"
        self.__data[x + 1][y - 1] = "X"

    def place_blinker(self, i, j):
        x = i - 1
        y = j - 1
        if 1 <= i <= 6 and 8 >= j >= 1:
            if self.__data[x][y] == "X" or self.__data[x + 1][y] == "X" or self.__data[x + 2][y] == "X":
                raise ValueError("occupied")
        else:
            raise ValueError("outside!")
        self.__data[x][y] = "X"
        self.__data[x + 1][y] = "X"
        self.__data[x + 2][y] = "X"

    def place_beacon(self, i, j):
        x = i
        y = j
        self.place_block(x + 2, y + 2)
        self.place_block(x, y)

    def place_spaceship(self, i, j):
        x = i - 1
        y = j - 1
        if 0 <= i <= 6 and 7 >= j >= 2:
            if self.__data[x][y] == "X" or self.__data[x + 1][y + 1] == "X" or self.__data[x + 2][y + 1] == "X" or \
                    self.__data[x + 2][y] == "X" or self.__data[x + 2][y - 1] == "X":
                raise ValueError("occupied")
        else:
            raise ValueError("outside")
        self.__data[x][y] = "X"
        self.__data[x + 1][y + 1] = "X"
        self.__data[x + 2][y + 1] = "X"
        self.__data[x + 2][y] = "X"
        self.__data[x + 2][y - 1] = "X"

    def place(self, i, j):
        self.__data[i - 1][j - 1] = "X"

    def set_empty(self, i, j):
        self.__data[i - 1][j - 1] = " "

    def get_data(self):
        return self.__data
