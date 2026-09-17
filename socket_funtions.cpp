#include <iostream>
#include <winsock2.h>
#include<cstring>

using namespace std;

bool servermsgreceive(char buffer[],SOCKET clientSocket){
    int bytesReceived = recv(
        clientSocket,
        buffer,
        1024,
        0
    );
        
    if(bytesReceived == SOCKET_ERROR){
        cout << "Recieved failed" <<'\n';
        return false;
    }else{
        buffer[bytesReceived] = '\0';
        cout << "Client says: " << buffer << '\n';
    }
    return true;
}

bool clientmsgsend(const char* message, SOCKET clientSocket){
    int bytesSent = send(
        clientSocket,
        message,
        strlen(message),
        0
    );
    if(bytesSent == SOCKET_ERROR){
        cout << "Send failed" << '\n';
        return false;
    }
    return true;

}