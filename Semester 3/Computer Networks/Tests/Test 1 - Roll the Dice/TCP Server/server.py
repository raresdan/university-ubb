import socket
import random
from time import sleep

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('192.168.10.64', 12345))
server.listen(2)

players = []


def roll_dice():
    return random.randint(1, 12)


while len(players) < 2:
    client_socket, client_address = server.accept()
    print(f"Connected to {client_address}")

    player_num = len(players)
    players.append(client_socket)
    client_socket.send(f"You are Player {player_num + 1}\n".encode())

for player_socket in players:
    player_socket.send("Both players are connected. The game is starting!\n".encode())

while True:
    player_roll = roll_dice()
    print(f"Player 1 rolled a {player_roll}.")
    players[0].send(f"Predict 'H' for higher or 'L' for lower\n".encode())
    players[1].send(f"Wait for other player...\n".encode())
    prediction = players[0].recv(1000).decode().strip()
    print(f"Player 1 predicted {prediction}")

    other_player_roll = roll_dice()
    print(f"Player 2 rolled a {other_player_roll}.")

    if ((prediction == 'H' and player_roll < other_player_roll) or
            (prediction == 'L' and player_roll > other_player_roll)):
        players[0].send("You lost!".encode())
        players[1].send("You won!".encode())
        print("Player 2 won!")
    else:
        players[0].send("You won!".encode())
        players[1].send("You lost!".encode())
        print("Player 1 won!")
    # for player_socket in players:
    #     player_socket.send("Play again? (Y/N): ".encode())
    #     play_again = player_socket.recv(1024).decode().strip()
    #     if play_again.lower() != 'y':
    #         for player in players:
    #             player.send("Game over. Other player abandoned the session.\nThanks for playing!\n".encode())
    #         server.close()
    #         exit()
    players[0], players[1] = players[1], players[0]
    print("The roles are reversed!\n")
    sleep(1)
