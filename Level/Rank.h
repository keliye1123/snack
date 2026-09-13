#pragma once
#include "../basic.h"
#include <iostream>

inline void InputRank_() {
    //监测
    GetCursorPos(&pt);
    HWND hwnd = GetForegroundWindow();
    ScreenToClient(hwnd,&pt);
    if (InArea_(0,0,100,50) && GetAsyncKeyState(VK_LBUTTON)& 0x0001) {
        exchange_level_flag = true;
        cur_level = 0;
        return;
    }
}

inline void RenderRank_() {
    settextstyle(100,0,"微软雅黑");
    outtextxy(300,10,"排行榜");

    settextstyle(50,0,"微软雅黑");
    outtextxy(150,150,"围城模式");
    settextstyle(50,0,"微软雅黑");
    outtextxy(500,150,"无限模式");
    for (int i=0;i<len1;i++) {
        char pl1[10];
        sprintf(pl1,"%d.%s %d",i+1,players1[i].name,players1[i].score);
        outtextxy(150,150 + i*50+50,pl1);
    }
    for (int i=0;i<len2;i++) {
        char pl2[10];
        sprintf(pl2,"%d.%s %d",i+1,players2[i].name,players2[i].score);
        outtextxy(500,150 + i*50+50,pl2);
    }

    setfillcolor(YELLOW);
    if (InArea_(0,0,100,50)) {
        setfillcolor(WHITE);
    }
    fillroundrect(0,0,100,50,10,10);
    settextstyle(0,0,"微软雅黑");
    outtextxy(30,10,"返回");
}