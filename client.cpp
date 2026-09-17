#include<iostream>
#include<winsock2.h>

using namespace std;

int main(){
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(result != 0){
        cout << "WSAStartup failed" << '\n';
        return 1;
    }
    cout << "Winsock initialized!" << '\n';
    SOCKET clientSock  = socket(AF_INET,SOCK_STREAM,0);
    if(clientSock == INVALID_SOCKET){
        cout << "sock fail: "<< WSAGetLastError() <<'\n';
        return 1;
    }
    cout << "client socket created!" <<'\n';
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    result = connect(
        clientSock,
        (sockaddr*)&serverAddress,
        sizeof(serverAddress)
    );
    if(result == SOCKET_ERROR){
        cout << "connection failed: "<< WSAGetLastError() <<'\n';
        return 1;
    }
    cout << "connected to server" << '\n';

    closesocket(clientSock);
    WSACleanup();
    return 0;
}