"""

@author: radu

 
"""
from tictactoe.ro.ubb.tictactoe.player.human import Human


class Game:
    def __init__(self, board, player1, player2):
        self.__board = board
        self.__player1 = player1
        self.__player2 = player2

        self.__last_move = None

    def play(self):
        while True:
            if self.__move(self.__player1, 1):
                break
            if self.__move(self.__player2, 2):
                break

    def __move(self, player, value):
        line, column = -1, -1
        if type(player) is Human:
            self.__draw_board()
            line, column = self.__read_data()
        self.__last_move = player.move(line, column, value)
        winner = self.__is_winner()
        if self.__is_over(self.__last_move) or winner:
            self.__show_game_over_status()
            return True
        return False

    @staticmethod
    def __read_data():
        try:
            line = int(input("Enter line: "))
        except ValueError as ve:
            print(ve)
            return
        try:
            column = int(input("Enter column: "))
        except ValueError as ve:
            print(ve)
            return
        return line, column

    def __draw_board(self):
        print(self.__board)

    def __is_winner(self):
        if self.__board.win(self.__player1.get_name()):
            return self.__player1
        if self.__board.win(self.__player2.get_name()):
            return self.__player2
        return False

    def __is_over(self, __last_move):
        pass

    def __show_game_over_status(self):
        pass
