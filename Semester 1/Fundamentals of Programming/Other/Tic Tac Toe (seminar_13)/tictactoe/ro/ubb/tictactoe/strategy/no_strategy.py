"""

@author: radu

 
"""
from tictactoe.ro.ubb.tictactoe.board.cell import Cell


class NoStrategy:
    def move(self, *args) -> Cell:
        """
        :param args:
        :return: the new cell or None
        """
        arg_list = []
        for arg in args:
            arg_list.append(arg)
