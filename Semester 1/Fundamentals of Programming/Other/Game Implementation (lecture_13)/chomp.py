from texttable import Texttable


class GameException(Exception):
    pass


class GameOver(Exception):
    pass


class Board:
    def __init__(self, width, height: int):
        self._width = width
        self._height = height
        # None - empty cell
        # <dash> - taken square
        # 'x' 'o' - explicit moves
        self._data = [[None] * self._width] * self._height
        self._data[0][0] = 'V'

    def move(self, symbol: str, row, col: int) -> None:
        if symbol not in ['X', 'O']:
            raise GameException("Incorrect symbol")
        if not (0 <= col < self._width) or not (0 <= row < self._height):
            raise GameException("Symbol outside the board")
        if self._data[row][col] is not None:
            raise GameException("Square already played")
        if row == 0 and col == 0:
            raise GameOver("You lost!")

    def __str__(self):
        board = Texttable()
        board.header(['/'] + list(range(1, self._width + 1)))
        board.add_row(['A'] + ['V'] + [' '] * (self._width - 1))
        for i in range(self._height - 1):
            board.add_row([chr(ord('B') + i)] + [' '] * self._width)

        return board.draw()


b = Board(5, 4)
b.move('X', 3, 3)
print(b)
