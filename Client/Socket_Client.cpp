
#include "Socket_Client.h"
#include <iostream>
#include <stdio.h>

SOCKET server_socket = -1;

//初始化socket库
bool InitSocket_() {
    WSADATA wsaData;
    if (0 == !WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        std::cerr << "WSAStartup fail!!:" <<WSAGetLastError()<< std::endl;
        return false;
    }
    return true;
}

//关闭
bool CloseSocket_() {
    if (0 != WSACleanup()) {
        printf("WSAStartup fail:%d\n", WSAGetLastError());
        return false;
    }
    return true;
}

SOCKET ConnectToServer_(int port,const std::string& ips) {
    //创建socket套接字 ：地址，端口号
    SOCKET serfd =  socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//ipv4/ipv6,数据类型,tcp/udp
    if (serfd == INVALID_SOCKET) {
        printf("socket fail:%d\n", WSAGetLastError());
        return -1;
    }

    //给socket绑定ip地址和端口号
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;//协议族
    servaddr.sin_port = htons(port);//端口号转为网络字节序
    servaddr.sin_addr.s_addr = inet_addr(ips.c_str());//服务器IP地址

    //连接到服务器
    std::cerr << "connect to server..." << serfd << std::endl;
    if (0 != connect(serfd,(struct sockaddr*)&servaddr,sizeof(servaddr))) {
        printf("connect fail:%d\n", WSAGetLastError());
        return -1;
    }
    int opt = 1;
    setsockopt(server_socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(opt));

    std::cerr << "connect to server success" << serfd << std::endl;

   return serfd;
}


