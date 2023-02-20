from unittest import TestCase

from src.board.board import Board


class TestAdvancing(TestCase):
    def setUp(self) -> None:
        self.board = Board()

    def test_advancing_beacon(self):
        self.board.place_beacon(1, 1)
        self.board.advancing()
        data = self.board.get_data()
        self.assertEqual(data[1][1], " ")
        self.assertEqual(data[2][2], " ")

    def test_advancing_block(self):
        self.board.place_block(1, 1)
        initial_data = self.board.get_data()
        self.board.advancing()
        data = self.board.get_data()
        self.assertEqual(initial_data, data)
