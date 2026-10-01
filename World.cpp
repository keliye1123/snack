#include "World.h"

#include <filesystem>
#include "Level/End.h"
#include "Level/Rank.h"

// #include "Level/Map3.h"
// #include "Level/Waiting.h"

World mainWorld;

POINT World::pt{};

World::World() {
    for (int i = 0;i <= HEIGHT/SIZE-1;i++ ) {
        for (int j = 0;j <= WIDTH/SIZE-1;j++ ) {
            mainWorld.map[i][j] = true;
        }
    }
}

void World::Init_() {
    levelManager = new LevelManager;
    leaderBoard = new LeaderBoard;
    LocalSnack = new Snack;
    LocalFood = new Food;
    main_UI = new UI;
}

void World::Begin_() const {
    if (levelManager -> GetFlag_()) {
        std::cout << "begin" << std::endl;
        levelManager -> SetFlag_(false);
        levelManager -> ChangeLevel();
        levelManager -> RunInit_();
    }
}

void World::Input_() const {
    levelManager -> RunInput_();
}

void World::Update_() const {
    levelManager -> RunUpdate_();
}

void World::Render_() const {
    levelManager -> RunRender_();
    main_UI -> DrawFPS_();
}

bool World::InArea_(int x1,int y1,int x2,int y2) {
    if (pt.x >= x1 and pt.x <= x2 && pt.y >= y1 and pt.y <= y2) {

        return true;
    }
    return false;
}
