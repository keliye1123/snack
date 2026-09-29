#include "World.h"

#include <filesystem>

#include "Level/Map1.h"
#include "Level/Map2.h"
#include "Level/Map3.h"
#include "Level/Menu.h"
#include "Level/End.h"
#include "Level/Set.h"
#include "Level/Rank.h"
#include "Level/Waiting.h"

World mainWorld;

void World::Init_() {
    levelManager = new LevelManager;
}

void World::Begin_() {
    if (levelManager -> GetFlag_()) {
        std::cout << "begin" << std::endl;
        levelManager -> SetFlag_(false);
        levelManager -> ChangeLevel();
        levelManager -> RunInit_();
    }
}

void World::Input_() {
    levelManager -> RunInput_();
}

void World::Update_() {
    levelManager -> RunUpdate_();
}

void World::Render_() {
    levelManager -> RunRender_();
    DrawFPS_();
}
