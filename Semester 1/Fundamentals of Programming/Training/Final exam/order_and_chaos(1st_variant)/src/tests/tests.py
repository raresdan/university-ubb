import unittest

from src.board.board import Board
from src.domain.computer import Computer


class TestComputer(unittest.TestCase):
    def setUp(self) -> None:
        self.board = Board()
        self.computer = Computer(self.board)

    def test_simulate(self):
        temp_board = self.computer.simulate(1, 1, "X")
        temp_data = temp_board.get_data()
        data = self.board.get_data()
        self.assertEqual(temp_data[0][0], "X")
        self.assertEqual(data[0][0], " ")

    def test_place(self):
        i, j, symbol = self.computer.place()
        self.assertTrue(1 <= i <= 6)
        self.assertTrue(1 <= j <= 6)
        self.assertTrue(symbol in ["X", "O"])

    def tearDown(self) -> None:
        pass
