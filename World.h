#pragma once

#include "Food/Food.h"
#include "LevelManager/LevelManager.h"
#include "LeaderBoard/LeaderBoard.h"
#include "Snack/Snack.h"
#include "UI/UI.h"
#include "Macro.h"

class World {
    //属性
public:
    LevelManager* levelManager = nullptr;   //场景管理器
    LeaderBoard* leaderBoard = nullptr;     //排行榜类
    Snack* LocalSnack = nullptr;            //本地蛇单例
    Food* LocalFood = nullptr;              //本地食物单例
    UI*   main_UI = nullptr;                //全局UI单例
    bool map[HEIGHT/SIZE][WIDTH/SIZE]{};      //全局地图单例
    static POINT pt;                               //全局鼠标单例

public:
    World();

    void Init_();

    void Begin_() const;

    void Input_() const;

    void Update_() const;

    void Render_() const;

    bool InArea_(int x1,int y1,int x2,int y2);

};

extern World mainWorld;