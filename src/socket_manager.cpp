#include "socket_manager.hpp"

#ifdef __3DS__
#include <3ds.h>
#endif

#include <iostream>


signed int SocketManager::connect(const std::string& address){

#ifdef __3DS__
    // allocate buffer for SOC service
    SOC_buffer = (unsigned int*)memalign(SOC_ALIGN, SOC_BUFFERSIZE);

    if(SOC_buffer == NULL) 
        return -2;

    // Now intialise soc:u service
    if ((ret = socInit((u32*)SOC_buffer, SOC_BUFFERSIZE)) != 0) 
        return -3;

#endif

    sock = socket (AF_INET, SOCK_STREAM, IPPROTO_IP);

    if (sock < 0) {
        return -4;
    }

    memset (&server, 0, sizeof (server));
    memset (&client, 0, sizeof (client));

    server.sin_family = AF_INET;
    server.sin_port = htons (1043);
    server.sin_addr.s_addr = inet_addr(address.c_str());

    if(inet_pton ( AF_INET, address.c_str(), &server.sin_addr.s_addr)<=0){
        printf ( "\nInvalid address ! This IP Address is not supported !\n" );
    }

    // int value = 1;
    // if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&value, sizeof(int))){
    //     printf("\n Error : SetSockOpt TCP_NODELAY Failed \n");
    // }


    csock = ::connect(sock, (struct sockaddr *) &server, sizeof(server));
    
	if(csock < 0)
        return -1;

    int flags = fcntl(sock, F_GETFL, 0);
    flags =  (flags | O_NONBLOCK);
    fcntl(sock, F_SETFL, flags);

    return csock;

}

std::string SocketManager::read(){
    char buffer[50];
    int i = 0;

    for(i = 0; i < 50; i++){
        char c;
        ::read(sock, &c, 1);

        buffer[i] = c;

        if(c == '\n')
            break;
    }

    return std::string(buffer, &buffer[i] - &buffer[0]);
}

void SocketManager::closeSocket(){
    close(csock);
}

signed int SocketManager::getSocket(){
    return csock;
}

bool SocketManager::sendPackage(const std::string msg){
    return (ssize_t)msg.size() == send(sock, msg.c_str(), msg.size(), 0);
}

bool SocketManager::sendSignal(Senal senal){
    const char* str = std::to_string(senal).append("\n").c_str();
    return sendPackage(str);
}

void SocketManager::setDisconnectListener(std::function<void()> func) {
    this->onDisconnect = func;
}
