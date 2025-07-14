#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define DEFAULT_BUFLEN 512

int main() {
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr;
    char response[DEFAULT_BUFLEN];

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) return 1;

    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        WSACleanup();
        return 2;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    if (connect(ConnectSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        WSACleanup();
        return 3;
    }

    std::cout << "Подключено к серверу!" << std::endl;

    int bytesReceived = recv(ConnectSocket, response, DEFAULT_BUFLEN - 1, 0);
    if (bytesReceived > 0) {
        response[bytesReceived] = '\0';
        std::cout << "Получено от сервера: " << response << std::endl;
    } else if (bytesReceived == 0) {
        std::cout << "Соединение закрыто." << std::endl;
    } else {
        std::cerr << "Ошибка получения данных!" << std::endl;
    }

    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}
