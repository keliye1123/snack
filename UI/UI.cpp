

#include "UI.h"
#include "../Macro.h"
#include <cstdio>

UI::UI() {
    delta_time = 0;
    FPS_gap = FPS_GAP;
    FPS_draw = 0;
}

void UI::SetDeltaTime_(long long time) {
    this -> delta_time = time;
}

long long UI::GetDeltaTime_() const{
    return delta_time;
}

void UI::SetFPSGap_(int time) {
    this -> FPS_gap = time;
}

int UI::GetFPSGap_() const{
    return FPS_gap;
}

void UI::SetFPSDraw_(long long time) {
    this -> FPS_draw = time;
}

long long UI::GetFPSDraw_() const{
    return FPS_draw;
}

//渲染帧率显示
void UI::DrawFPS_() {
    char s[20];
    if (FPS_gap == FPS_GAP) {
        FPS_draw = delta_time > 0 ? (long long)(1000/delta_time) : 0;
        FPS_gap = 0;
    }else {
        FPS_gap++;
    }

    sprintf(s,"FPS：%lld",FPS_draw);
    settextstyle(38,0,"微软雅黑");
    outtextxy(90,0,s);
}
