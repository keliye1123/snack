#pragma once

#include "LevelManager/LevelManager.h"

class World {
    //属性
public:
    LevelManager* levelManager = nullptr;

public:
    void Init_();

    void Begin_();

    void Input_();

    void Update_();

    void Render_();
};

extern World mainWorld;