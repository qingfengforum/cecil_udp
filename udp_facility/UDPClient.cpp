#include "UDPClient.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

bool UDPClient::startUDPClient(const char* service_ip, uint16_t port)
{
    struct sockaddr_in service_addr;

    // create socket
    socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_fd_ < 0)
    {
        perror("create socket fail!\n");
        return false;
    }

    // connect to the server
    memset(&service_addr_, 0, sizeof(service_addr_));
    service_addr_.sin_family = AF_INET;
    service_addr_.sin_addr.s_addr = inet_addr(service_ip);
    service_addr_.sin_port = htons(port);
    if (connect(socket_fd_, (struct sockaddr *)&service_addr_, sizeof(service_addr_)) < 0)
    {
        perror("connect service error\n");
        return false;
    }

    printf("== start udp client success ==\n");
    printf("service ip   : %s\n", service_ip);
    printf("service port : %u\n", port);

    return true;
}

bool UDPClient::stopUDPClient()
{
    if (socket_fd_ != -1)
    {
        return close(socket_fd_);
    }

    return true;
}

int UDPClient::UDPClientSend(const char *buf, int msg_len)
{
    return sendto(socket_fd_, buf, msg_len, 0, (struct sockaddr *)&service_addr_, sizeof(service_addr_));
}

int UDPClient::UDPClientRecv(char *buf, int buf_size)
{
    struct sockaddr_in src;
    socklen_t len = 0;
    return recvfrom(socket_fd_, buf, buf_size, 0, (struct sockaddr*)&src, &len);
}

/*------- static funcs -------------*/
uint8_t UDPClient::getCheckSum(char* buf, uint32_t len)
{
    uint8_t check_sum = buf[0];
    for (int i = 1; i < len; i++)
    {
        check_sum = check_sum ^ buf[i];
    }

    return check_sum;
}