from unittest import TestCase

from src.board.board import Board
from src.domain.computer import Computer


class TestComputer(TestCase):
    def setUp(self) -> None:
        pass

    def test_computer(self):
        computer = Computer('🟡')
        self.assertEqual(computer.get_chip(), '🔴')
        self.assertEqual(computer.get_enemy_chip(), '🟡')

    def test_str(self):
        computer = Computer('🔵')
        expected_output = "Computer is playing with 🔴"
        self.assertEqual(str(computer), expected_output)

    def test_simulation(self):
        board = Board()
        computer = Computer('🟡')
        temporary_board = computer.simulation(board, '🔴', 4)
        board.move('🔴', 4)
        self.assertEqual(temporary_board.get_board(), board.get_board())

    def test_move_win(self):
        board = Board()
        computer = Computer('🔵')
        board.move('🔴', 1)
        board.move('🔴', 2)
        board.move('🔴', 3)
        move = computer.move(board)
        self.assertTrue(board.possible_moves(move))

    def test_move_block(self):
        board = Board()
        computer = Computer('🔵')
        board.move('🔵', 1)
        board.move('🔵', 2)
        board.move('🔵', 3)
        move = computer.move(board)
        self.assertTrue(board.possible_moves(move))

    def test_move_random(self):
        board = Board()
        computer = Computer('🔵')
        move = computer.move(board)
        self.assertTrue(isinstance(move, int) and 0 <= move <= 6)
        self.assertTrue(board.possible_moves(move))

    def tearDown(self) -> None:
        pass
