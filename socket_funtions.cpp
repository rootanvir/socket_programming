#include <iostream>
#include <winsock2.h>
#include <cstring>

using namespace std;


bool msgreceive(char buffer[], SOCKET clientSocket)
{
    int totalReceived = 0;

    while (true)
    {
        char ch;

        int bytesReceived = recv(
            clientSocket,
            &ch,
            1,
            0
        );

        if (bytesReceived == SOCKET_ERROR)
        {
            cout << "Receive failed" << '\n';
            return false;
        }

        if (bytesReceived == 0)
        {
            cout << "Other side disconnected!" << '\n';
            return false;
        }

        if (ch == '\n')
        {
            break;
        }

        buffer[totalReceived] = ch;
        totalReceived++;

        if (totalReceived >= 1024)
        {
            break;
        }
    }

    buffer[totalReceived] = '\0';

    cout << "Other: " << buffer << '\n';

    return true;
}

bool msgsend(const char* message, SOCKET clientSocket)
{
    char sendBuffer[1025];

    strcpy(sendBuffer, message);
    strcat(sendBuffer, "\n");

    int totalSent = 0;
    int totalLength = strlen(sendBuffer);

    while (totalSent < totalLength)
    {
        int bytesSent = send(
            clientSocket,
            sendBuffer + totalSent,
            totalLength - totalSent,
            0
        );

        if (bytesSent == SOCKET_ERROR)
        {
            cout << "Send failed" << '\n';
            return false;
        }

        totalSent += bytesSent;
    }

    return true;
}