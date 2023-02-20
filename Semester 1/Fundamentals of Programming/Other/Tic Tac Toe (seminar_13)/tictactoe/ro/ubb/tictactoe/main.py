"""

@author: radu

 
"""
from tictactoe.ro.ubb.tictactoe.board.board import Board
from tictactoe.ro.ubb.tictactoe.game import Game
from tictactoe.ro.ubb.tictactoe.player.computer import Computer
from tictactoe.ro.ubb.tictactoe.player.human import Human
from tictactoe.ro.ubb.tictactoe.strategy.no_strategy import NoStrategy

if __name__ == '__main__':
    # todo: validations

    board = Board(3, 3)
    strategy = NoStrategy()
    player1 = Computer("X", board, strategy)
    player2 = Human("0", board)
    game = Game(board, player1, player2)
    game.play()

    print("bye")
