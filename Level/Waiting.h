#pragma once
#include"../together.h"
#include "../Thread/poll.h"
#include "../Client/Socket_Client.h"

inline void InitWaiting_() {
    if (exchange_level_flag == true) {
        //与服务器建立连接
        //初始化socket库
        InitSocket_();

        server_socket = ConnectToServer_(SPORT,"8.156.69.189");
        if (server_socket == -1) {
            exchange_level_flag = true;
            std::cout << "连接到服务器失败" << std::endl;
            cur_level = 0;
            return;
        }
        pool.enqueue([] {
            std::string ac;
            ac.clear();
            ac.resize(1024);
            std::cout<<"等待匹配中"<<std::endl;
            int readn = recv(server_socket,&ac[0],1024,0);
            ac.resize(readn);
            int res = stoi(ac);

            if (res == ENTER_SUCCESS) {
                char buf[32];
                int len = sprintf(buf,"%d",ENTER_SUCCESS);
                send(server_socket,buf,len,0);
                std::cout<<"匹配成功"<<std::endl;
                //接收编号
                ac.clear();
                ac.resize(1024);
                std::cout<<"等待接受玩家编号"<<std::endl;
                int readn = recv(server_socket,&ac[0],1024,0);
                ac.resize(readn);
                cur_player = stoi(ac);
                std::cout<<"接收到玩家编号"<<std::endl;
                std::cout<<"cur_player: "<<cur_player<<(cur_player == 1 ? "蓝色" :"绿色")<<std::endl;

                exchange_level_flag = true;
                cur_level = 6;
            }
            else if (res == EXIT_QUEUE) {
                std::cout << "收到EXIT_QUEUE退出队列成功" << std::endl;
                exchange_level_flag = true;
                cur_level = 0;
            }
        });


        exchange_level_flag = false;
    }

}

inline void InputWaiting_() {
    //输入监测
    GetCursorPos(&pt);
    HWND hwnd = GetForegroundWindow();//获取当前窗口句柄
    ScreenToClient(hwnd,&pt);//将坐标转为相对于窗口的坐标
    if (InArea_(0,0,100,50) && GetAsyncKeyState(VK_LBUTTON)& 0x0001) {
        char buf[32];
        int len = sprintf(buf,"%d",EXIT_QUEUE);
        send(server_socket,buf,len,0);
        std::cout << "发送EXIT_QUEUE退出等待队列消息" << std::endl;
    }
}

inline void UpdateWaiting_() {


}

inline void RenderWaiting_() {

    setfillcolor(YELLOW);
    if (InArea_(0,0,100,50)) {
        setfillcolor(WHITE);
    }
    fillroundrect(0,0,100,50,10,10);
    settextstyle(0,0,"微软雅黑");
    outtextxy(30,10,"返回");

    settextstyle(150,0,"微软雅黑");
    outtextxy(250,150,"匹配中");
}