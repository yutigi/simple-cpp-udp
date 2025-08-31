// simple_udp_client.cpp
// A simple UDP client in C++

#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8888);

    std::string message;
    char buffer[1024];
    int serverAddrLen = sizeof(serverAddr);

    std::cout << "Enter message to send (type 'exit' to quit):\n";
    while (true) {
        std::getline(std::cin, message);
        if (message == "exit") break;
        sendto(clientSocket, message.c_str(), message.size(), 0, (sockaddr*)&serverAddr, serverAddrLen);
        int recvLen = recvfrom(clientSocket, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&serverAddr, &serverAddrLen);
        if (recvLen == SOCKET_ERROR) {
            std::cerr << "recvfrom failed" << std::endl;
            break;
        }
        buffer[recvLen] = '\0';
        std::cout << "Received from server: " << buffer << std::endl;
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}

// g++.exe .\simple_udp_client.cpp -o .\simple_udp_client.exe -lws2_32
