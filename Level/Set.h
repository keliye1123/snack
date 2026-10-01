# pragma once
#include "../World.h"

inline char Set_s[3];

inline void SetInit_() {

}

inline void SetInput_() {
    GetCursorPos(&World::pt);
    HWND hwnd = GetForegroundWindow();
    ScreenToClient(hwnd,&World::pt);
    if (mainWorld.InArea_(0,0,100,50) && GetAsyncKeyState(VK_LBUTTON)& 0x0001) {
        mainWorld.levelManager -> SetChangeLevel("Menu");
        mainWorld.levelManager -> SetFlag_(true);
        return;
    }
    if (mainWorld.InArea_(300,390,350,410) && (GetAsyncKeyState(VK_LBUTTON)& 0x0001)) {
        if (mainWorld.LocalSnack -> GetSpeed_() < mainWorld.LocalSnack -> GetMinSpeed_()) {
            mainWorld.LocalSnack -> SetSpeed_(mainWorld.LocalSnack -> GetSpeed_() + 1);
            mainWorld.LocalSnack -> SetGap_(mainWorld.LocalSnack -> GetSpeed_());
        }
    }
    if ((mainWorld.InArea_(515,375,535,425) || mainWorld.InArea_(500,390,550,410)) &&(GetAsyncKeyState(VK_LBUTTON) & 0x0001) ) {
        if (mainWorld.LocalSnack -> GetSpeed_() > mainWorld.LocalSnack -> GetMaxSpeed_()) {
            mainWorld.LocalSnack -> SetSpeed_(mainWorld.LocalSnack -> GetSpeed_() - 1);
            mainWorld.LocalSnack -> SetGap_(mainWorld.LocalSnack -> GetSpeed_());
        }
    }

    sprintf(Set_s,"%d",mainWorld.LocalSnack -> GetMinSpeed_() + 1 - mainWorld.LocalSnack -> GetSpeed_());
}

inline void SetUpdate_() {

}

inline void SetRRender_() {

    setfillcolor(YELLOW);
    if (mainWorld.InArea_(0,0,100,50)) {
        setfillcolor(WHITE);
    }
    fillroundrect(0,0,100,50,10,10);
    settextstyle(0,0,"微软雅黑");
    outtextxy(30,10,"返回");

    setfillcolor(YELLOW);
    if (mainWorld.InArea_(300,390,350,410)) {
        setfillcolor(WHITE);
    }
    fillrectangle(300,390,350,410);

    setfillcolor(YELLOW);
    if (mainWorld.InArea_(515,375,535,425) || mainWorld.InArea_(500,390,550,410)) {
        setfillcolor(WHITE);
    }
    fillrectangle(515,375,535,425);
    fillrectangle(500,390,550,410);

    settextstyle(50,20,"微软雅黑");
    outtextxy(400,300,"速度");
    outtextxy(400,370,Set_s);

}