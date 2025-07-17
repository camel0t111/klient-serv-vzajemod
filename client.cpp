#include <iostream>              // типу cout
#include <winsock2.h>           // сокети для win
#include <ws2tcpip.h>           // inet функції

#pragma comment(lib, "Ws2_32.lib")  // бібліотека обов'язкова

#define SERVER_PORT 8080         // порт на якому слухаємо
#define DEFAULT_BUFLEN 512       // розмір буфера

int main() {
    WSADATA wsaData;                          // щоб ініціалізувать сокети
    SOCKET ListenSocket = INVALID_SOCKET;     // сокет який слухає
    SOCKET ClientSocket = INVALID_SOCKET;     // сокет клієнта після з'єднання
    struct sockaddr_in serverAddr;            // адреса сервера
    const char* message = "Привіт від сервера!"; // що шлемо клієнту

    // запуск сокетів
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) return 1;

    // створюєм TCP сокет
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        WSACleanup();
        return 2;
    }

    // налаштовуєм IP/порт
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY; // всі інтерфейси

    // прив’язуєм сокет
    if (bind(ListenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(ListenSocket);
        WSACleanup();
        return 3;
    }

    // починаєм слухати
    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(ListenSocket);
        WSACleanup();
        return 4;
    }

    std::cout << "Чекаємо клієнта на порту " << SERVER_PORT << "..." << std::endl;

    // чекаєм поки хтось підключиться
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        closesocket(ListenSocket);
        WSACleanup();
        return 5;
    }

    // шлемо клієнту повідомлення
    send(ClientSocket, message, (int)strlen(message), 0);
    std::cout << "Повідомлення відправлено клієнту." << std::endl;

    // закриваєм сокети
    closesocket(ClientSocket);
    closesocket(ListenSocket);
    WSACleanup();

    return 0;
}
