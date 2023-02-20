class Board:

    def __init__(self):
        self.__data = [['⚪' for _ in range(7)] for _ in range(6)]

    def get_board(self):
        return self.__data

    def __str__(self):
        table = "    1    2    3    4    5    6    7  \n"
        table += "  +----+----+----+----+----+----+----+\n"
        for i in range(6):
            for j in range(7):
                table += ' | '
                table += str(self.__data[i][j])
            table += ' |\n'
            table += "  +----+----+----+----+----+----+----+ \n"
        return table

    def win(self):
        """
        Checks every possibility of a player making a connect four( rows, columns and diagonals)
        :return: True if anybody won, False otherwise
        """
        # Checks if there are four chips of the same color on a row
        for i in range(6):
            for j in range(4):
                if self.__data[i][j] != '⚪':
                    if self.__data[i][j] == self.__data[i][j + 1]:
                        if self.__data[i][j] == self.__data[i][j + 2]:
                            if self.__data[i][j] == self.__data[i][j + 3]:
                                return True
        # Checks if there are four chips of the same color on a col
        for i in range(3):
            for j in range(7):
                if self.__data[i][j] != '⚪':
                    if self.__data[i][j] == self.__data[i + 1][j]:
                        if self.__data[i][j] == self.__data[i + 2][j]:
                            if self.__data[i][j] == self.__data[i + 3][j]:
                                return True
        # Checks if there are four chips of the same color on a diagonal (from left to right)
        for i in range(3):
            for j in range(4):
                if self.__data[i][j] != '⚪':
                    if self.__data[i][j] == self.__data[i + 1][j + 1]:
                        if self.__data[i][j] == self.__data[i + 2][j + 2]:
                            if self.__data[i][j] == self.__data[i + 3][j + 3]:
                                return True
        # Checks if there are four chips of the same color on a diagonal (from right to left)
        for i in range(3):
            for j in range(6, 2, -1):
                if self.__data[i][j] != '⚪':
                    if self.__data[i][j] == self.__data[i + 1][j - 1]:
                        if self.__data[i][j] == self.__data[i + 2][j - 2]:
                            if self.__data[i][j] == self.__data[i + 3][j - 3]:
                                return True
        return False

    def draw(self):
        """
        Checks if all the fields are occupied by chips and still no player won
        :return: True is so, False otherwise
        """
        for i in range(6):
            for j in range(7):
                if self.__data[i][j] == '⚪':
                    return False
        return True

    def move(self, chip, col):
        """
        Places the chip on the lowest empty row possible
        :param chip: The chip that wants to be moved
        :param col: the column where to be placed
        :return: True if the move was performed in optimal conditions, False otherwise
        """
        i = 5
        while i >= 0:
            if self.__data[i][col] == '⚪':
                self.__data[i][col] = chip
                return True
            i = i - 1
        return False

    def possible_moves(self, col):
        """
        Checks if there are any possible moves on a certain column
        :param col: the column on which the function checks for empty spaces
        :return: True if a move can be performed on this column, False otherwise
        """
        i = 5
        while i >= 0:
            if self.__data[i][col] == '⚪':
                return True
            i = i - 1
        return False
