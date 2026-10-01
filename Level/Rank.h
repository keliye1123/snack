#pragma once

inline void InitRank_() {

}

inline void InputRank_() {
    //监测
    GetCursorPos(&World::pt);
    HWND hwnd = GetForegroundWindow();
    ScreenToClient(hwnd,&World::pt);
    if (mainWorld.InArea_(0,0,100,50) && GetAsyncKeyState(VK_LBUTTON)& 0x0001) {
        mainWorld.levelManager -> SetFlag_(true);
        mainWorld.levelManager -> SetChangeLevel("Menu");
        return;
    }
}

inline void UpdateRank_() {

}

inline void RenderRank_() {
    mainWorld.leaderBoard -> RenderLeaderBoard_();

    setfillcolor(YELLOW);
    if (mainWorld.InArea_(0,0,100,50)) {
        setfillcolor(WHITE);
    }
    fillroundrect(0,0,100,50,10,10);
    settextstyle(0,0,"微软雅黑");
    outtextxy(30,10,"返回");
}