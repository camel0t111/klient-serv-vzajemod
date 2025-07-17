#include <iostream>              // базовий ввід/вивід, типу cout і т.д.
#include <winsock2.h>           // сокети для вінди
#include <ws2tcpip.h>           // inet_pton і всяке таке

#pragma comment(lib, "Ws2_32.lib")  // обов'язково підключити бібліотеку, інакше не збереш

#define SERVER_IP "127.0.0.1"   // локалхост, типу сервер у себе ж на компі
#define SERVER_PORT 8080        // порт, де слухає сервер
#define DEFAULT_BUFLEN 512      // скільки символів макс читаєм за раз

int main() {
    WSADATA wsaData;                    // спец штука щоб віндовс дав доступ до сокетів
    SOCKET ConnectSocket = INVALID_SOCKET; // сокет клієнта
    struct sockaddr_in serverAddr;      // структура з адресою сервера
    char response[DEFAULT_BUFLEN];      // сюди кладемо те що сервер нам відправить

    // запускаємо "двигун" для сокетів
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) return 1;

    // створюєм TCP сокет
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        WSACleanup(); // чистимо якшо не получилось
        return 2;
    }

    // налаштовуєм IP і порт сервера
    serverAddr.sin_family = AF_INET;               // IPv4
    serverAddr.sin_port = htons(SERVER_PORT);      // порт в норм формат
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr); // строка в IP

    // конектимось до сервера
    if (connect(ConnectSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        WSACleanup();
        return 3;
    }

    std::cout << "Підключено до сервера!" << std::endl;

    // слухаємо шо сервер скаже
    int bytesReceived = recv(ConnectSocket, response, DEFAULT_BUFLEN - 1, 0);
    if (bytesReceived > 0) {
        response[bytesReceived] = '\0'; // ставим кінець рядка
        std::cout << "Отримано від сервера: " << response << std::endl;
    } else if (bytesReceived == 0) {
        std::cout << "Сервер закрив з’єднання." << std::endl;
    } else {
        std::cerr << "Помилка отримання!" << std::endl;
    }

    // закриваєм сокет, все гуд
    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}
#include <iostream>              // базовий ввід/вивід, типу cout і т.д.
#include <winsock2.h>           // сокети для вінди
#include <ws2tcpip.h>           // inet_pton і всяке таке

#pragma comment(lib, "Ws2_32.lib")  // обов'язково підключити бібліотеку, інакше не збереш

#define SERVER_IP "127.0.0.1"   // локалхост, типу сервер у себе ж на компі
#define SERVER_PORT 8080        // порт, де слухає сервер
#define DEFAULT_BUFLEN 512      // скільки символів макс читаєм за раз

int main() {
    WSADATA wsaData;                    // спец штука щоб віндовс дав доступ до сокетів
    SOCKET ConnectSocket = INVALID_SOCKET; // сокет клієнта
    struct sockaddr_in serverAddr;      // структура з адресою сервера
    char response[DEFAULT_BUFLEN];      // сюди кладемо те що сервер нам відправить

    // запускаємо "двигун" для сокетів
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) return 1;

    // створюєм TCP сокет
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        WSACleanup(); // чистимо якшо не получилось
        return 2;
    }

    // налаштовуєм IP і порт сервера
    serverAddr.sin_family = AF_INET;               // IPv4
    serverAddr.sin_port = htons(SERVER_PORT);      // порт в норм формат
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr); // строка в IP

    // конектимось до сервера
    if (connect(ConnectSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        WSACleanup();
        return 3;
    }

    std::cout << "Підключено до сервера!" << std::endl;

    // слухаємо шо сервер скаже
    int bytesReceived = recv(ConnectSocket, response, DEFAULT_BUFLEN - 1, 0);
    if (bytesReceived > 0) {
        response[bytesReceived] = '\0'; // ставим кінець рядка
        std::cout << "Отримано від сервера: " << response << std::endl;
    } else if (bytesReceived == 0) {
        std::cout << "Сервер закрив з’єднання." << std::endl;
    } else {
        std::cerr << "Помилка отримання!" << std::endl;
    }

    // закриваєм сокет, все гуд
    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}
