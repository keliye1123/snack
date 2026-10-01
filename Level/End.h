#pragma once
#include "../basic.h"
#include "../InputMethod/InputMethod.h"

inline bool key_lock = false;
inline ExMessage msg;

inline void InitEnd_() {


}

inline void InputEnd_() {
     //监测输入
    peekmessage(&msg, EM_KEY);
    if (msg.message == WM_KEYDOWN && !key_lock) {
        key_lock = true;

        //未处于输入法时回车：完成输入并退出
        if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && inputMethod.GetStatus_() == false && !mainWorld.LocalSnack ->GetName_().empty()) {
            std::cout << mainWorld.LocalSnack -> GetScore_() << std::endl;
            mainWorld.leaderBoard -> RenderLeaderUpdate_();
            mainWorld.levelManager -> SetChangeLevel("Menu");
            mainWorld.levelManager -> SetFlag_(true);
            return;
        }

        std::string temp = mainWorld.LocalSnack -> GetName_();
        inputMethod.RunInputMethod_(temp);
        mainWorld.LocalSnack -> SetName_(temp);
    }
    else if (msg.message == WM_KEYUP && key_lock) key_lock = false;

}

inline void UpdateEnd_() {

}

inline void RenderEnd_() {
    inputMethod.Draw_(200,400 + 50);
    settextstyle(50,20,"微软雅黑");
    outtextxy(200,300,"最终的分：");
    char s[20];
    sprintf(s ,"%d",mainWorld.LocalSnack -> GetScore_());
    outtextxy(400,300,s);
    outtextxy(200,400,"输入昵称：");
    outtextxy(400,400,mainWorld.LocalSnack -> GetName_().c_str());
}


