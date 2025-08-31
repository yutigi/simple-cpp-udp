// simple_udp_server.cpp
// A simple UDP server in C++

#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8888);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "UDP server listening on port 8888..." << std::endl;
    char buffer[1024];
    sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);

    while (true) {
        int recvLen = recvfrom(serverSocket, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&clientAddr, &clientAddrLen);
        if (recvLen == SOCKET_ERROR) {
            std::cerr << "recvfrom failed" << std::endl;
            break;
        }
        buffer[recvLen] = '\0';
        std::cout << "Received: " << buffer << std::endl;
        // Echo back
        sendto(serverSocket, buffer, recvLen, 0, (sockaddr*)&clientAddr, clientAddrLen);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}

// Compile with: g++.exe .\simple_udp_server.cpp -o .\simple_udp_server.exe -lws2_32
