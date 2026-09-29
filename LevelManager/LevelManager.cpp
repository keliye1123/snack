
#include "LevelManager.h"


//输入地图
#include "../Level/Menu.h"
#include "../Level/Map1.h"
#include "../Level/Map2.h"
#include "../Level/Map3.h"
#include "../Level/End.h"
#include "../Level/Rank.h"
#include "../Level/Set.h"
#include "../Level/Waiting.h"


LevelManager::LevelManager() {

    AddLevel("Menu",MenuInit_,MenuInput_,MenuUpdate_,MenuRender_);
    AddLevel("Map1",InitMap1_,InPutMap1_,UpdateMap1_,RenderMap1_);
    AddLevel("Map2",InitMap2_,InPutMap2_,UpdateMap2_,RenderMap2_);
    AddLevel("Map3",InitMap3_,InputMap3_,UpdateMap3_,RenderMap3_);
    AddLevel("End",InitEnd_,InputEnd_,UpdateEnd_,RenderEnd_);
    AddLevel("Rank",InitRank_,InputRank_,UpdateRank_,RenderRank_);
    AddLevel("Set",SetInit_,SetInput_,SetUpdate_,SetRRender_);
    AddLevel("Waiting",InitWaiting_,InputWaiting_,UpdateWaiting_,RenderWaiting_);
    CurrentLevel = GetLevelByName("Menu");

    Exchange_Flag = true;

    changeLevel = "Menu";
}

Level LevelManager::GetLevelByName(const std::string& LevelName) {
    return this -> LevelMap.find(LevelName)->second;
}

void LevelManager::AddLevel(const std::string& LevelName,const std::function<void()>& Init,const std::function<void()>& Input,const std::function<void()>& Update,const std::function<void()>& Render) {
    Level temp(LevelName,Init,Input,Update,Render);
    LevelMap.insert({LevelName,temp});
}

void LevelManager::ChangeLevel() {
    CurrentLevel = GetLevelByName(changeLevel);
}

void LevelManager::RunInit_() {
    CurrentLevel.RunInit_();
}

void LevelManager::RunInput_() {
    CurrentLevel.RunInput_();
}

void LevelManager::RunUpdate_() {
    CurrentLevel.RunUpdate_();
}

void LevelManager::RunRender_() {
    CurrentLevel.RunRender_();
}

Level LevelManager::GetCurrentLevel() {
    return this -> CurrentLevel;
}
