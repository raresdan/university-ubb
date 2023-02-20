"""

@author: radu

 
"""
from abc import abstractmethod

from tictactoe.ro.ubb.tictactoe.board.cell import Cell


class Player:
    def __init__(self, name, board):
        self.__name = name
        self._board = board

    def get_name(self):
        return self.__name

    @abstractmethod
    def move(self, *args) -> Cell:
        """
        :param args:
        :return: the new cell or None
        """
        pass
