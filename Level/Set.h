# pragma once
# include "../basic.h"
#include <iostream>

inline char Set_s[3];

inline void SetInput_() {
    GetCursorPos(&pt);
    HWND hwnd = GetForegroundWindow();
    ScreenToClient(hwnd,&pt);
    if (InArea_(0,0,100,50) && GetAsyncKeyState(VK_LBUTTON)& 0x0001) {
        cur_level = 0;
        exchange_level_flag = true;
        return;
    }
    if (InArea_(300,390,350,410) && (GetAsyncKeyState(VK_LBUTTON)& 0x0001)) {
        if (speed <= 6) {
            speed += 2;
            speed_gap = speed;
        }
    }
    if ((InArea_(515,375,535,425) || InArea_(500,390,550,410)) &&(GetAsyncKeyState(VK_LBUTTON) & 0x0001) ) {
        if (speed >= 4) {
            speed -= 2;
            speed_gap = speed;
        }
    }

    sprintf(Set_s,"%d",10 - speed);
}

inline void SetRRender_() {

    setfillcolor(YELLOW);
    if (InArea_(0,0,100,50)) {
        setfillcolor(WHITE);
    }
    fillroundrect(0,0,100,50,10,10);
    settextstyle(0,0,"Î¢ÈíÑÅºÚ");
    outtextxy(30,10,"·µ»Ø");

    setfillcolor(YELLOW);
    if (InArea_(300,390,350,410)) {
        setfillcolor(WHITE);
    }
    fillrectangle(300,390,350,410);

    setfillcolor(YELLOW);
    if (InArea_(515,375,535,425) || InArea_(500,390,550,410)) {
        setfillcolor(WHITE);
    }
    fillrectangle(515,375,535,425);
    fillrectangle(500,390,550,410);

    settextstyle(50,20,"Î¢ÈíÑÅºÚ");
    outtextxy(400,300,"ËÙ¶È");
    outtextxy(400,370,Set_s);

}