#pragma once
#include"../together.h"
#include "../Thread/poll.h"
#include "../Client/Socket_Client.h"

inline std::string ac;
inline int res_x;
inline int res_y;

inline void InitMap3_() {
    if (exchange_level_flag == true) {

        for (int i = 0;i <= HEIGHT/SIZE-1;i++ ) {
            for (int j = 0;j <= WIDTH/SIZE-1;j++ ) {
                map[i][j] = true;
            }
        }

        InitSnack1_();
        InitSnack2_();

        exchange_level_flag = false;

    }
}

inline void InputMap3_() {
    if (cur_player == 1) {
        if (GetAsyncKeyState('A') && player1_dir != RIGHT && player1_dir != LEFT) {
            player1_dir = LEFT;
            exchange_dir = true;
        }
        else if (GetAsyncKeyState('W') && player1_dir != DOWN && player1_dir != UP) {
            player1_dir = UP;
            exchange_dir = true;
        }
        else if (GetAsyncKeyState('D') && player1_dir != LEFT && player1_dir != RIGHT) {
            player1_dir = RIGHT;
            exchange_dir = true;
        }
        else if (GetAsyncKeyState('S') && player1_dir != UP && player1_dir != DOWN) {
            player1_dir = DOWN;
            exchange_dir = true;
        }
    }
    else {
        if (GetAsyncKeyState('A') && player2_dir != RIGHT && player2_dir != LEFT) {
            player2_dir = LEFT;
            exchange_dir = true;
        }
        else if (GetAsyncKeyState('W') && player2_dir != DOWN && player2_dir != UP) {
            player2_dir = UP;
            exchange_dir = true;
        }
        else if (GetAsyncKeyState('D') && player2_dir != LEFT && player2_dir != RIGHT) {

            player2_dir = RIGHT;
            exchange_dir = true;
        }
        else if (GetAsyncKeyState('S') && player2_dir != UP && player2_dir != DOWN) {
            player2_dir = DOWN;
            exchange_dir = true;
        }
    }

}

inline void UpdateMap3_() {
        //每次更新发送状态
        if (cur_player == 1) {
            char buf[32];
            int len = sprintf(buf, "%d", player1_dir);
            send(server_socket,buf,len,0);
        }
        else {
            char buf[32];
            int len = sprintf(buf, "%d", player2_dir);
            send(server_socket,buf,len,0);
        }
    //阻塞等待服务器更新状态再进行逻辑更新
    ac.clear();
    ac.resize(1024);
    int readn = recv(server_socket,&ac[0],1024,0);
    ac.resize(readn);
    int Dir = stoi(ac.substr(0,1));
    if (Dir == ERRORS) {//网络异常对局结束
        exchange_level_flag = true;
        std::cout << "对方网络异常，对局结束" <<std::endl;
        std::cout << "你的得分为："<< ((cur_player == 1) ? player1_score : player2_score) << std::endl;
        std::cout << "对方的得分为："<< ((cur_player == 1) ? player2_score : player1_score) << std::endl;
        cur_level = 0;
        return ;
    }
    if (Dir == PLAY1WIN || Dir == PLAY2WIN) {
        exchange_level_flag = true;
        if ((cur_player == 1 && Dir == PLAY1WIN) || (cur_player == 2 && Dir == PLAY2WIN)) std::cout << "你赢了" <<std::endl;
        else std::cout << "你输了" <<std::endl;
        std::cout << "你的得分为："<< ((cur_player == 1) ? player1_score : player2_score) << std::endl;
        std::cout << "对方的得分为："<< ((cur_player == 1) ? player2_score : player1_score) << std::endl;
        cur_level = 0;
        return ;
    }
    res_x = stoi(ac.substr(1,3));
    res_y = stoi(ac.substr(4,3));
    player1_score = stoi(ac.substr(7,4));
    player2_score = stoi(ac.substr(11,4));
    if (cur_player == 1) {
        if (Dir== 0) player2_dir = LEFT;
        else if (Dir == 1) player2_dir = UP;
        else if (Dir == 2)player2_dir = RIGHT;
        else if (Dir == 3) player2_dir = DOWN;
    } else {
        if (Dir == 0) player1_dir = LEFT;
        else if (Dir == 1) player1_dir = UP;
        else if (Dir == 2)player1_dir = RIGHT;
        else if (Dir == 3) player1_dir = DOWN;
    }

    //逻辑更新
        UpdatePlay1_(res_x,res_y);
        UpdatePlay2_(res_x,res_y);

}

//渲染背景3
inline void DrawBackground3_() {

    setlinecolor(WHITE);
    setlinestyle(PS_SOLID,2);
    for (int i = 0;i*SIZE <= WIDTH;i++ ) {

        line(i*SIZE,0,i*SIZE,750);
    }
    for (int j = 0;j*SIZE <= HEIGHT;j++) {
        line(0,j*SIZE,900,j*SIZE);
    }
}

inline void DrawFood1_() {
        setfillcolor(RED);
        fillrectangle(res_x,res_y,res_x + SIZE,res_y+ SIZE);
}

inline void DrawPlayerScore_() {
    char s[20];
    sprintf(s,"玩家1得分：%d",player1_score);
    settextcolor(BLUE);
    settextstyle(50,0,"");
    outtextxy(0,HEIGHT,s);

    sprintf(s,"玩家2得分：%d",player2_score);
    settextcolor(GREEN);
    settextstyle(50,0,"");
    outtextxy(450,HEIGHT,s);
}


inline void RenderMap3_() {
    DrawBackground3_();
    DrawFood1_();
    DrawSnack1_();
    DrawSnack2_();
    DrawPlayerScore_();
}
