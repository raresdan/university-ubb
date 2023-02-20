from src.board.board import Board
from src.domain.computer import Computer
from src.domain.player import Player
from colorama import *


class Ui:
    @staticmethod
    def menu():
        print(f"{Fore.MAGENTA}  Welcome to Connect Four! {Style.RESET_ALL}")
        print()

        print(f"{Fore.LIGHTGREEN_EX}         MENU        ")
        print()
        print("1 - Player VS Computer")
        print("2 - Player VS Player")
        print(f"0 - Exit the game{Style.RESET_ALL}")

    @staticmethod
    def choose_color(colors):
        index = 1
        for color in colors:
            print(f"#{index} - {color}")
            index += 1
        while True:
            while True:
                try:
                    option = int(input("> "))
                    break
                except ValueError as ve:
                    print(f"Invalid option!", ve)
            try:
                print(f"You picked {colors[option - 1]}!")
                color = colors[option - 1]
                colors.remove(color)
                return color
            except IndexError as ie:
                print("Invalid option!", ie)

    @staticmethod
    def valid_col(col):
        try:
            col == int(col)
        except ValueError:
            return False
        if 1 <= int(col) <= 7:
            return True
        return False

    def player_vs_computer(self):
        colors = ['🟡', '🔵', '🟠', '🟢', '🟣', '🟤']
        print(f"{Fore.LIGHTBLUE_EX}Player{Style.RESET_ALL}")
        print("Choose your color: ")
        print()
        chip = self.choose_color(colors)
        print()
        print("Enter your name: ")
        name = input("> ")
        player = Player(name, chip)
        print()
        computer = Computer(chip)
        board = Board()
        print(player)
        print(computer)
        print()
        print(board)
        while not board.draw():
            col1 = input(f"{Fore.LIGHTBLUE_EX}{player.get_name()}{Style.RESET_ALL} choose a column: ")
            while not self.valid_col(col1):
                col1 = input("Column must be an integer between 1 and 7: ")
                print()
            col1 = int(col1)
            col1 -= 1
            while not board.move(chip, col1):
                col1 = input("The chosen column is full! Please choose another one: ")
                print()
                while not self.valid_col(col1):
                    col1 = input("Column must be an integer between 1 and 7: ")
                    print()
                col1 = int(col1)
                col1 -= 1
            print(board)
            if board.win():
                print(f"{Fore.GREEN}{player.get_name()} WON!{Style.RESET_ALL}")
                break
            print(f"{Fore.CYAN}Waiting for computer's move . . .{Style.RESET_ALL}")
            col2 = computer.move(board)
            board.move(computer.get_chip(), int(col2))
            print(f"{Fore.CYAN}The computer has made its decision!{Style.RESET_ALL}")
            print()
            print(board)
            if board.win():
                print(f"{Fore.RED}Computer WON!{Style.RESET_ALL}")
                break
        if board.draw():
            print(f"{Fore.LIGHTBLACK_EX}DRAW!{Style.RESET_ALL}")
        print()

    def player_vs_player(self):
        colors = ['🟡', '🔵', '🟠', '🟢', '🟣', '🟤', '🔴', '👁️', '🕸️', '🎱', '🏀', '⚽', '🌍', '🌑', '☀️', '❄️']
        print(f"{Fore.LIGHTBLUE_EX}Player 1{Style.RESET_ALL}")
        print("Choose your color: ")
        print()
        chip1 = self.choose_color(colors)
        print()
        print("Enter your name: ")
        name1 = input("> ")
        player1 = Player(name1, chip1)
        print()
        print(f"{Fore.LIGHTBLUE_EX}Player 2{Style.RESET_ALL}")
        print("Choose your color: ")
        print()
        chip2 = self.choose_color(colors)
        print()
        print("Enter your name: ")
        name2 = input("> ")
        player2 = Player(name2, chip2)
        board = Board()
        print(player1)
        print(player2)
        print()
        print(board)
        while not board.draw():
            col1 = input(f"{Fore.LIGHTBLUE_EX}{player1.get_name()}{Style.RESET_ALL} choose a column: ")
            while not self.valid_col(col1):
                col1 = input("Column must be an integer between 1 and 7: ")
            col1 = int(col1)
            col1 -= 1
            while not board.move(chip1, col1):
                col1 = input("The chosen column is full! Please choose another one: ")
                while not self.valid_col(col1):
                    col1 = input("Column must be an integer between 1 and 7: ")
                col1 = int(col1)
                col1 -= 1
            print(board)
            if board.win():
                print(f"{Fore.GREEN}{player1.get_name()} WON!{Style.RESET_ALL}")
                break
            col2 = input(f"{Fore.MAGENTA}{player2.get_name()}{Style.RESET_ALL} choose a column: ")
            while not self.valid_col(col2):
                col2 = input("Column must be an integer between 1 and 7: ")
            col2 = int(col2)
            col2 -= 1
            while not board.move(chip2, col2):
                col2 = input("The chosen column is full! Please choose another one: ")
                while not self.valid_col(col2):
                    col2 = input("Column must be an integer between 1 and 7: ")
                col2 = int(col2)
                col2 -= 1
            print(board)
            if board.win():
                print(f"{Fore.GREEN}{player2.get_name()} WON!{Style.RESET_ALL}")
                break
        if board.draw():
            print(f"{Fore.LIGHTBLACK_EX}DRAW!{Style.RESET_ALL}")
        print()

    def run_menu(self):
        self.menu()
        while True:
            while True:
                try:
                    print()
                    option = int(input("Enter the desired option: "))
                    print()
                    break
                except ValueError as ve:
                    print("Invalid option!", ve)
            if 2 >= option >= 0:
                if option == 1:
                    self.player_vs_computer()
                if option == 2:
                    self.player_vs_player()
                if option == 0:
                    print(f"{Fore.MAGENTA}Thank you for playing! Game exited successfully!{Style.RESET_ALL}")
                    break
            else:
                print("Invalid option!")
