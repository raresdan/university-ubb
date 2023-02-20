"""

@author: radu

 
"""
from abc import abstractmethod

from tictactoe.ro.ubb.tictactoe.board.cell import Cell
from tictactoe.ro.ubb.tictactoe.player.player import Player


class Computer(Player):
    def __init__(self, strategy, name, board):
        super().__init__(name, board)
        self.__strategy = strategy

    @abstractmethod
    def move(self, *args) -> Cell:
        """
        :param args:
        :return: the new cell or None
        """
        pass