// udp_mock_client.cpp
// UDP client that sends 100,000 Vector3 values every 0.2 seconds

#include <iostream>
#include <vector>
#include <winsock2.h>
#include <thread>
#include <chrono>
#include <random>
#pragma comment(lib, "ws2_32.lib")

struct Vector3 {
    float x, y, z;
};

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
    int serverAddrLen = sizeof(serverAddr);

    std::vector<Vector3> data(5458);
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1000.0f, 1000.0f);

    while (true) {
        // Fill with random data
        for (auto& v : data) {
            v.x = dist(rng);
            v.y = dist(rng);
            v.z = dist(rng);
        }
        // Send as raw bytes
        int bytesToSend = static_cast<int>(data.size() * sizeof(Vector3));
        int sent = sendto(clientSocket, reinterpret_cast<const char*>(data.data()), bytesToSend, 0, (sockaddr*)&serverAddr, serverAddrLen);
        if (sent == SOCKET_ERROR) {
            std::cerr << "sendto failed" << std::endl;
            break;
        }
        std::cout << "Sent " << sent << " bytes" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}

// g++.exe .\udp_mock_client.cpp -o udp_mock_client.exe -lws2_32
