#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <queue>
using namespace std;



enum Msg {
    LEFT,         //0
    UP,           //1
    RIGHT,        //2
    DOWN,         //3
    QUEUE_FULL,   //4，匹配队列已满
    EXIT_QUEUE,    //5，客户端请求退出等待队列
    ERRORS,         //6，网络异常，对局结束
    PLAY1WIN,     //7，玩家1胜利
    PLAY2WIN,     //8，玩家2胜利
    ENTER_SUCCESS //9，匹配成功
};

#define WIDTH  900              //窗口宽度
#define HEIGHT 750              //窗口高度
#define SIZE   75               //单个方格大小
#define speed 3

//玩家1的蛇头位置
#define PLAYER1_HEAD_X    300
#define PLAYER1_HEAD_Y    300
#define PLAYER1_DIRECTION RIGHT  //玩家1蛇的初始方向

//玩家2的蛇头位置
#define PLAYER2_HEAD_X    300
#define PLAYER2_HEAD_Y    375
#define PLAYER2_DIRECTION RIGHT  //玩家2蛇的初始方向

//食物
typedef struct food {
    int x;
    int y;
    bool exists;
} Food;

//蛇节点定义
typedef struct snack {
    int x;
    int y;
    struct snack *next;
}Node;

#define MAXSIZE_QUEUE  10       //等待队列的最大等待数量
#define MAXSIZE_ROOM   5        //最大房间数量
#define MAXSIZE_PEOPLE 2        //单个房间人数的最大数量
#define MAXLEN         1024     //报文的最大长度
#define SPORT 5005              //服务器端口

class TcpServe {       //TCP通信的服务端类

    //属性
private:
    int socket_s_ = 0;       //服务端的socket，-1表示未连接或连接已断开，>=0表示有效的socket
    unsigned short port_ = 0;//通讯端口

    std::string client_ip_;  //存放客户端Ip



    //方法
public:

    std::string GetClientIP_() const {
        return client_ip_;
    }

    bool Listen_(const unsigned short& port) {
        //第一步创建服务端socket
        socket_s_ = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_s_ == -1) {
            std::cout << "错误：服务端socket创建失败" << std::endl;
            return false;
        }

        port_ = port;

        //第二步：把服务端用于通信的ip和端口绑定到socket上
        //把服务端用于通信的ip地址和端口绑定到socket上
        struct sockaddr_in server_addr;     //用于存放服务端ip地址和端口的数据结构
        memset(&server_addr,0,sizeof(server_addr));
        server_addr.sin_family = AF_INET;   //指定协议
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);    //服务端任意网卡的ip都可以用于通信
        server_addr.sin_port = htons(port_);//指定通信端口，普通用户只能用1024以上的端口
        //绑定服务端的ip和端口
        //绑定成功返回0，失败返回-1
        if (bind(socket_s_,(struct sockaddr*)&server_addr,sizeof(server_addr)) == -1 ) {
            close(socket_s_);
            std::cout << "错误：服务端绑定ip与端口失败" << std::endl;
            return false;
        }

        //第三步：把socket设置为可连接（监听）的状态。
        //返回-1错误，返回0为成功监听
        //listen的第二个参数为监听队列数量
        if (listen(socket_s_,5) == -1) {
            std::cout << "错误：服务端监听失败" << std::endl;
            close(socket_s_);
            return false;
        }

        return true;
    }

    //返回接收到的客户端句柄，参数一为传出客户端句柄
    int Accept_(int& socket_c_) {

        //暂时存储客户端ip地址
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        //第四步：受理客户端的连接请求，如果没有客户端连上来，accept()函数将阻塞等待。
        socket_c_ = accept(socket_s_,(struct sockaddr*)&client_addr,&client_addr_len);//获得客户端句柄，接收客户端的IP地址

        //保存客户端ip地址
        client_ip_ = inet_ntoa(client_addr.sin_addr);

        if (socket_c_ == -1) {
            close(socket_s_);
            std::cout << "错误：服务端报文接收失败" << std::endl;
            return -1;
        }

        return 0;
    }

    //接受指定客户端发来的报文,参数一为指定客户端句柄，参数二为传出报文，参数三为传出报文最大长度
    int Receive_(int socket_c_,std::string &ac,unsigned int maxlen) {
        if (socket_c_ == -1) return -1;
        //接收客户端的请求报文，如果客户端没有发送请求报文，recv()函数将阻塞等待。
        //如果客户端已断开连接，recv()函数将返回0.
        //recv收到消息返回消息长度，网络异常返回-1,四次挥手正常断开连接返回0
        ac.clear();
        ac.resize(maxlen);
        int readn = recv(socket_c_,&ac[0],maxlen,0);
        if (readn <= 0) {
            ac.clear();
            return readn;
        }
        ac.resize(readn);
        return readn;
    }

    //发送报文到指定客户端，参数一为客户端句柄，参数二为发送的报文
    bool Send_(int socket_c_,std::string rs) {
        if (socket_c_ == -1) return false;
        //向客户端发送回应报文。
        //send返回-1为失败，大于等于0为写入字节数，
        if (send(socket_c_,rs.data(),rs.size(),0) == -1) return false;
        return true;
    }

    //关闭指定客户端句柄
    void CloseSocket_(int socket_c_) const{
        //第六步：关闭socket，释放资源
        close(socket_c_);    //关闭客户端连上来的socket
        // close(socket_s_);    //关闭服务端用于监听的socket
    }

};
