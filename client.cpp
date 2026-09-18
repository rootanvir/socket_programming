#include <iostream>
#include <winsock2.h>
#include "socket_funtions.h"
#include <thread>
#include<conio.h>
#include<atomic>


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
    cout << "Winsock initialized!" << '\n';
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET)
    {
        cout << "sock fail: " << WSAGetLastError() << '\n';
        return 1;
    }
    cout << "client socket created!" << '\n';
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    result = connect(
        clientSocket,
        (sockaddr *)&serverAddress,
        sizeof(serverAddress));
    if (result == SOCKET_ERROR)
    {
        cout << "connection failed: " << WSAGetLastError() << '\n';
        return 0;
    }
    cout << "connected to server" << '\n';

    std::atomic<bool> connected(true);
    
    char buffer[1024];

    thread receiveThread([&](){
        while(connected){
            if(!msgreceive(buffer, clientSocket)){
                connected = false;
                break;
            }
        }
    });
    while (connected)
    {
        char message[1024];
        cin.getline(message, 1024);
        if(!connected){
            break;
        }
        if (!msgsend(message, clientSocket))
        {
            connected = false;
            break;
        }
    }

    receiveThread.join();

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}