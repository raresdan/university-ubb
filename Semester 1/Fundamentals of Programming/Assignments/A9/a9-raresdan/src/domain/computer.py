import copy
from random import randint


class Computer:
    def __init__(self, enemy_chip):
        self.__chip = '🔴'
        self.__enemy_chip = enemy_chip

    def get_chip(self):
        return self.__chip

    def get_enemy_chip(self):
        return self.__enemy_chip

    def __str__(self):
        return f"Computer is playing with {self.__chip}"

    @staticmethod
    def simulation(board, chip, col):
        """
        Creates a temporary board, simulating one step ahead
        :param board: the board on which the next move is performed
        :param chip: the chip which is moved in the next simulated move
        :param col: the column on which the simulated move is performed
        :return: a new board with the simulated move
        """
        temporary_board = copy.deepcopy(board)
        temporary_board.move(chip, col)
        return temporary_board

    def move(self, board):
        """
        The "AI's" move. It checks if it can win the next move and performs the winning move.
        If the player can win in the next move, it blocks the player from winning.
        If the game cannot end for neither of the player in exactly one move, it performs a random move.
        :param board: the board on which the moves are performed
        :return: the column on which the "AI" decided to make its move
        """
        for col in range(7):
            if board.possible_moves(col):
                temporary_board = self.simulation(board, self.__chip, col)
                if temporary_board.win():
                    return col
        for col in range(7):
            if board.possible_moves(col):
                temporary_board = self.simulation(board, self.__enemy_chip, col)
                if temporary_board.win():
                    return col
        while True:
            col = randint(0, 6)
            if board.possible_moves(col):
                return col
