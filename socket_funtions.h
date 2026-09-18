#ifndef SOCKET_FUNCTIONS_H
#define SOCKET_FUNCTIONS_H

#include <winsock2.h>

bool msgreceive(char buffer[], SOCKET clientSocket);

bool msgsend(const char* message, SOCKET clientSocket);

#endif