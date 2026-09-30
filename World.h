#pragma once

#include "Food/Food.h"
#include "LevelManager/LevelManager.h"
#include "LeaderBoard/LeaderBoard.h"
#include "Snack/Snack.h"

class World {
    //属性
public:
    LevelManager* levelManager = nullptr;   //场景管理器
    LeaderBoard* leaderBoard = nullptr;     //排行榜类
    Snack* LocalSnack = nullptr;            //本地蛇单例
    Food* Food = nullptr;                   //本地食物单例


public:
    void Init_();

    void Begin_();

    void Input_();

    void Update_();

    void Render_();
};

extern World mainWorld;