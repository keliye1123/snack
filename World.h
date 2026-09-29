#pragma once

#include "LevelManager/LevelManager.h"

class World {
    //属性
private:
    LevelManager* currentLevel = nullptr;

public:
    void Input_();

    void Update_();

    void Render_();
};

extern World mainWorld;