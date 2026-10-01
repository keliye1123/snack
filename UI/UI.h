#pragma once

class UI {
    //属性
    long long delta_time;      //单帧时间间隔
    int FPS_gap;               //设置FPS的渲染间隔帧数
    long long FPS_draw;        //用于绘制FPS的值

    //方法
public:
    UI();

    void SetDeltaTime_(long long time);

    [[nodiscard]] long long GetDeltaTime_() const;

    void SetFPSGap_(int time);

    [[nodiscard]] int GetFPSGap_() const;

    void SetFPSDraw_(long long time);

    [[nodiscard]] long long GetFPSDraw_()const;

    //渲染帧率显示
    void DrawFPS_();
};



