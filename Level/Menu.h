#pragma once
#include <iostream>

#include"../World.h"
//主菜单

inline void MenuInit_() {

}

inline void MenuInput_() {
    //输入监测
    GetCursorPos(&World::pt);
    HWND hwnd = GetForegroundWindow();//获取当前窗口句柄
    ScreenToClient(hwnd,&World::pt);//将坐标转为相对于窗口的坐标
    if (mainWorld.InArea_(100,600,200,650) &&(GetAsyncKeyState(VK_LBUTTON)& 0x8000) ) {
        mainWorld.levelManager -> SetChangeLevel("Map1");
        mainWorld.levelManager -> SetFlag_(true);
    }
    else if (mainWorld.InArea_(400,600,500,650) && GetAsyncKeyState(VK_LBUTTON)& 0x8000) {
        mainWorld.levelManager -> SetChangeLevel("Map2");
        mainWorld.levelManager -> SetFlag_(true);
    }
    else if (mainWorld.InArea_(700,600,800,650) && GetAsyncKeyState(VK_LBUTTON)& 0x8000) {
        mainWorld.levelManager -> SetChangeLevel("Set");
        mainWorld.levelManager -> SetFlag_(true);
    }
    else if (mainWorld.InArea_(700,500,800,550) && GetAsyncKeyState(VK_LBUTTON)& 0x8000) {
        mainWorld.levelManager -> SetChangeLevel("Rank");
        mainWorld.levelManager -> SetFlag_(true);
    }
    else if (mainWorld.InArea_(400,500,500,550) && GetAsyncKeyState(VK_LBUTTON)& 0x8000) {
        mainWorld.levelManager -> SetChangeLevel("Waiting");
        mainWorld.levelManager -> SetFlag_(true);
    }
    else if (mainWorld.InArea_(WIDTH - 100,0,WIDTH,50) && GetAsyncKeyState(VK_LBUTTON)& 0x8000){
        mainWorld.leaderBoard -> WriteFile_();
        exit(0);
    }


}

inline void MenuUpdate_() {

}

inline void MenuRender_() {
    //渲染
    settextcolor(BLACK);
    settextstyle(0,0,"微软雅黑");
    setbkmode(TRANSPARENT);


    setfillcolor(YELLOW);
    if (mainWorld.InArea_(100,600,200,650)) {

        setfillcolor(WHITE);
    }
    fillroundrect(100,600,200,650,10,10);
    outtextxy(110,610,"围城模式");

    setfillcolor(YELLOW);
    if (mainWorld.InArea_(400,600,500,650)) {
        setfillcolor(WHITE);
    }
    fillroundrect(400,600,500,650,10,10);
    outtextxy(410,610,"无限模式");

    setfillcolor(YELLOW);
    if (mainWorld.InArea_(700,600,800,650)) {
        setfillcolor(WHITE);
    }
    fillroundrect(700,600,800,650,10,10);
    outtextxy(730,610,"设置");

    setfillcolor(YELLOW);
    if (mainWorld.InArea_(700,500,800,550)) {
        setfillcolor(WHITE);
    }
    fillroundrect(700,500,800,550,10,10);
    outtextxy(720,515,"排行榜");

    setfillcolor(YELLOW);
    if (mainWorld.InArea_(400,500,500,550)) {
        setfillcolor(WHITE);
    }
    fillroundrect(400,500,500,550,10,10);
    outtextxy(410,515,"联机模式");

    setfillcolor(YELLOW);
    if (mainWorld.InArea_(WIDTH - 100,0,WIDTH,50)) {
        setfillcolor(WHITE);
    }
    fillroundrect(WIDTH - 100,0,WIDTH,50,10,10);
    outtextxy(WIDTH - 100 + 30,10,"退出");

    settextstyle(150,0,"微软雅黑");
    outtextxy(250,150,"贪吃蛇");
}

