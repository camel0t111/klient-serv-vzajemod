#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define SERVER_PORT 8080
#define DEFAULT_BUFLEN 512

int main() {
    WSADATA wsaData;
    SOCKET ListenSocket = INVALID_SOCKET, ClientSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr;
    const char* message = "Привіт від сервера!";

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) return 1;

    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        WSACleanup();
        return 2;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(ListenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(ListenSocket);
        WSACleanup();
        return 3;
    }

    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(ListenSocket);
        WSACleanup();
        return 4;
    }

    std::cout << "Ожидание клиента на порту " << SERVER_PORT << "..." << std::endl;

    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        closesocket(ListenSocket);
        WSACleanup();
        return 5;
    }

    send(ClientSocket, message, (int)strlen(message), 0);
    std::cout << "Сообщение отправлено клиенту." << std::endl;

    closesocket(ClientSocket);
    closesocket(ListenSocket);
    WSACleanup();

    return 0;
}
