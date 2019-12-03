#ifndef _UDPCLIENT_H_
#define _UDPCLIENT_H_

#include <stdint.h>
#include <arpa/inet.h>

class UDPClient
{
public:
    bool startUDPClient(const char *service_ip, uint16_t port);
    bool stopUDPClient();

    int UDPClientSend(const char *buf, int msg_len);
    int UDPClientRecv(char *buf, int buf_size);

    static uint8_t getCheckSum(char* buf, uint32_t len);
private:
    int socket_fd_;
    struct sockaddr_in service_addr_;
};




#endif