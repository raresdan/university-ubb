from unittest import TestCase

from src.board.board import Board


class TestBoard(TestCase):
    def setUp(self) -> None:
        pass

    def test_board(self):
        board = Board()
        self.assertEqual(type(board), Board)

    def test_str(self):
        board = Board()
        expected_output = "    1    2    3    4    5    6    7  \n  " \
                          "+----+----+----+----+----+----+----+\n " \
                          "| ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ |\n  " \
                          "+----+----+----+----+----+----+----+ \n " \
                          "| ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ |\n  " \
                          "+----+----+----+----+----+----+----+ \n " \
                          "| ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ |\n  " \
                          "+----+----+----+----+----+----+----+ \n " \
                          "| ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ |\n  " \
                          "+----+----+----+----+----+----+----+ \n " \
                          "| ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ |\n  " \
                          "+----+----+----+----+----+----+----+ \n " \
                          "| ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ | ⚪ |\n " \
                          " +----+----+----+----+----+----+----+ \n"
        self.assertEqual(str(board), expected_output)

    def test_win_col(self):
        board = Board()
        self.assertEqual(board.win(), False)
        for _ in range(4):
            board.move('🟡', 4)
        self.assertEqual(board.win(), True)

    def test_win_row(self):
        board = Board()
        self.assertEqual(board.win(), False)
        for i in range(4):
            board.move('🟡', i)
        self.assertEqual(board.win(), True)

    def test_win_diagonal_left_right(self):
        board = Board()
        self.assertEqual(board.win(), False)
        board.move('🟡', 1)
        board.move('🔵', 2)
        board.move('🟡', 2)
        board.move('🔵', 3)
        board.move('🔵', 3)
        board.move('🟡', 3)
        board.move('🔵', 4)
        board.move('🔵', 4)
        board.move('🔵', 4)
        board.move('🟡', 4)
        self.assertEqual(board.win(), True)

    def test_win_diagonal_right_left(self):
        board = Board()
        self.assertEqual(board.win(), False)
        board.move('🟡', 4)
        board.move('🔵', 3)
        board.move('🟡', 3)
        board.move('🔵', 2)
        board.move('🔵', 2)
        board.move('🟡', 2)
        board.move('🔵', 1)
        board.move('🔵', 1)
        board.move('🔵', 1)
        board.move('🟡', 1)
        self.assertEqual(board.win(), True)

    def test_move(self):
        board = Board()
        self.assertEqual(board.move('🟡', 4), True)
        for _ in range(6):
            board.move('🟡', 4)
        self.assertEqual(board.move('🟡', 4), False)

    def test_draw(self):
        board = Board()
        self.assertEqual(board.draw(), False)
        for i in range(6):
            for j in range(7):
                board.move('🟡', j)
        self.assertEqual(board.draw(), True
                         )

    def test_possible_moves(self):
        board = Board()
        self.assertEqual(board.possible_moves(4), True)
        for _ in range(6):
            board.move('🟡', 4)
        self.assertEqual(board.possible_moves(4), False)

    def tearDown(self) -> None:
        pass
