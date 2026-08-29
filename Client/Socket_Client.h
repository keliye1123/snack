#pragma once
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <string>
#define SPORT 5005//服务器端口号

enum Msg {
    LEF,         //0
    U,           //1
    RIGH,        //2
    DOW,         //3
    QUEUE_FULL,   //4，匹配队列已满
    EXIT_QUEUE,    //5,客户端请求退出等待队列
    ERRORS,       //6,网络异常，对局结束
    PLAY1WIN,     //7，玩家1胜利
    PLAY2WIN,     //8，玩家2胜利
    ENTER_SUCCESS //9，匹配成功
};

//服务器socket
extern SOCKET server_socket;

//初始化socket库
bool InitSocket_();
//关闭socket库
bool CloseSocket_();
//监听客户端链接,返回服务端socket
SOCKET ConnectToServer_(int port,const std::string& ips);
//处理消息
bool ProcessMsg_(SOCKET s);