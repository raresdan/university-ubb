#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[1024];

    const char* HOST = "192.168.0.103";
    int PORT = 12345;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    if (inet_pton(AF_INET, HOST, &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Invalid address/Address not supported" << std::endl;
        return 1;
    }


    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return 1;
    }

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
            std::cerr << "Failed to receive data" << std::endl;
            break;
        }
        std::string data(buffer);
        std::cout << data << std::endl;
        if (data.find("The game is starting") != std::string::npos) {
            break;
        }
    }

 
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
            std::cerr << "Failed to receive data" << std::endl;
            break;
        }
        std::string player_message(buffer);
        if (player_message.find("Predict") != std::string::npos) {
            std::string response;
            std::cout << player_message;
            std::getline(std::cin, response);
            if (send(clientSocket, response.c_str(), response.size(), 0) < 0) {
                std::cerr << "Failed to send data" << std::endl;
                break;
            }
        } else {
            std::cout << player_message << std::endl;
        }

        memset(buffer, 0, sizeof(buffer));
        if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
            std::cerr << "Failed to receive data" << std::endl;
            break;
        }
        std::string status(buffer);
        std::cout << status << std::endl;

        memset(buffer, 0, sizeof(buffer));
        if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
            std::cerr << "Failed to receive data" << std::endl;
            break;
        }
        std::string pa(buffer);
        std::cout << pa << std::endl;

        std::string play_again;
        std::getline(std::cin, play_again);
        if (send(clientSocket, play_again.c_str(), play_again.size(), 0) < 0) {
            std::cerr << "Failed to send data" << std::endl;
            break;
        }

        if (play_again != "Y") {
            break;
        }
    }

    close(clientSocket);

    return 0;
}