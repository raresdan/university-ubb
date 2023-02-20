"""

@author: radu

 
"""
from texttable import Texttable

from tictactoe.ro.ubb.tictactoe.board.cell import Cell


class Board:
    def __init__(self, width, height):
        self.__width = width
        self.__height = height
        self.__data = [[None for _ in range(self.__width)] for _ in range(self.__height)]

    def __str__(self):
        board = Texttable()
        board.add_row(['/'] + list(range(1, self.__width + 1)))
        for i in range(self.__height):
            for j in range(1):
                board.add_row([chr(ord('A') + i)] + [str(self.__data[i][j]), str(self.__data[i][j + 1]),
                                                     str(self.__data[i][j + 2])])
        return board.draw()

    def win(self, symbol):
        for i in range(self.__width):
            for j in range(self.__height):
                if self.__data[i][j] is not None:
                    if self.__data[i][j] == self.__data[i][j + 1] == self.__data[i][j + 2] == symbol:
                        return True

        for i in range(self.__width):
            for j in range(self.__height):
                if self.__data[i][j] is not None:
                    if self.__data[i][j] == self.__data[i + 1][j] == self.__data[i + 2][j] == symbol:
                        return True

        for i in range(self.__width):
            for j in range(self.__height):
                if self.__data[i][j] is not None:
                    if self.__data[i][j] == self.__data[i + 1][j + 1] == self.__data[i + 2][j + 2] == symbol:
                        return True

        for i in range(self.__width):
            for j in range(self.__height):
                if self.__data[i][j] is not None:
                    if self.__data[i][j] == self.__data[i + 1][j - 1] == self.__data[i + 2][j - 2] == symbol:
                        return True

        return False

    def draw(self):
        for i in range(self.__width):
            for j in range(self.__height):
                if self.__data[i][j] is not None:
                    return False
        return True

    def move(self, row, column, symbol):
        if self.__data[row][column] is None:
            self.__data[row][column] = Cell(row, column, symbol)
            return True
        return False
