from unittest import TestCase

from src.domain.chip import Chip
from src.domain.player import Player


class TestChip(TestCase):
    def setUp(self) -> None:
        pass

    def test_chip(self):
        chip = Chip('🟡')
        self.assertEqual(chip.get_color(), '🟡')

    def tearDown(self) -> None:
        pass


class TestPlayer(TestCase):
    def setUp(self) -> None:
        pass

    def test_player(self):
        player = Player("John", '🟡')
        self.assertEqual(player.get_name(), "John")
        self.assertEqual(player.get_chip(), '🟡')

    def test_str(self):
        player = Player("John", '🟡')
        expected_output = f"Player {player.get_name()} is playing with {player.get_chip()}!"
        self.assertEqual(str(player), expected_output)

    def tearDown(self) -> None:
        pass
