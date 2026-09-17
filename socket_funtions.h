#ifndef SOCKET_FUNCTIONS_H
#define SOCKET_FUNCTIONS_H

#include <winsock2.h>

bool servermsgreceive(char buffer[], SOCKET clientSocket);

bool clientmsgsend(const char* message, SOCKET clientSocket);

#endif