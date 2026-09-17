#include <iostream>
#include <winsock2.h>
#include "socket_funtions.h"
using namespace std;

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        cout << "WSAStartup failed" << '\n';
        return 1;
    }
    cout << "winsock initailed" << '\n';
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        cout << "socket connection failed" << '\n';
        cout << "Error: " << WSAGetLastError() << '\n';
        return 1;
    }
    cout << "socket conncetion sucessful!" << '\n';
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    cout << "connection configured" << '\n';
    result = bind(
        sock,
        (sockaddr *)&serverAddress,
        sizeof(serverAddress));
    if (result == SOCKET_ERROR)
    {
        cout << "bind failed" << '\n';
        cout << "Error: " << WSAGetLastError() << '\n';
    }
    cout << "Socket bound successfully !" << '\n';
    result = listen(sock, 5);
    if (result == SOCKET_ERROR)
    {
        cout << "Listen failed" << '\n';
        cout << "Error: " << WSAGetLastError() << '\n';
    }
    cout << "Server Listening..." << '\n';

    SOCKET clientSocket = accept(sock, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Accept fail" << '\n';
        cout << "Error: " << WSAGetLastError() << '\n';
    }
    cout << "client connected !" << '\n';

    char buffer[1024];
    while (true)
    {

        if (!servermsgreceive(buffer, clientSocket))
        {
            break;
        }
        clientmsgsend("Hello Client!", clientSocket);
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}