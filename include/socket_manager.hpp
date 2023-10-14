#pragma once

#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <unistd.h>
#include <stdarg.h>

#include "signal.hpp"

#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string>
#include <vector>
#include <functional>


class SocketManager{

    const int SOC_ALIGN       = 0x1000;
    const int SOC_BUFFERSIZE  = 0x100000;

    unsigned int *SOC_buffer = NULL;
    signed int sock = -1, csock = -1;


    std::function<void()> onDisconnect;

public:

    int ret;

	struct sockaddr_in client;
	struct sockaddr_in server;

    /** @returns 0 if successful, negative numbers otherwise. */
    signed int connect(const std::string& address);
    
    /** @returns true if successful, false otherwise. */
    bool sendPackage(const std::string message);

    /** @returns true if successful, false otherwise. */
    bool sendSignal(Senal senal);

    std::string read();

    void closeSocket();

    signed int getSocket();

    void setDisconnectListener(std::function<void()> func);
};
