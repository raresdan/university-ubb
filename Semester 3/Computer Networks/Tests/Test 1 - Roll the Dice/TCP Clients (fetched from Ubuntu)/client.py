import socket

HOST = '192.168.0.103'  # Update this with the server's IP address
PORT = 12345

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))

while True:
    data = client.recv(1024).decode('utf-8')
    print(data)

    if "The game is starting" in data:
        break

while True:
    player_message = client.recv(1024).decode('utf-8')
    
    if "Predict" in player_message:
        response = input(player_message)
        client.send(response.encode('utf-8'))
    else:
        print(player_message)

    status = client.recv(1024).decode('utf-8')
    print(status)

    pa = client.recv(1024).decode('utf-8')
    print(pa)
    play_again = input()
    client.send(play_again.encode('utf-8'))

    if play_again.lower() != 'y':
        break

client.close()
