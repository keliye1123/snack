
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

    AddLevel("Menu",nullptr,MenuInput_,nullptr,MenuRender_);
    AddLevel("Map1",InitMap1_,InPutMap1_,UpdateMap1_,RenderMap1_);
    AddLevel("Map2",InitMap2_,InPutMap2_,UpdateMap2_,RenderMap2_);
    AddLevel("Map3",InitMap3_,InputMap3_,UpdateMap3_,RenderMap3_);
    AddLevel("End",InitEnd_,InputEnd_,nullptr,RenderEnd_);
    AddLevel("Rank",InputRank_,nullptr,nullptr,RenderRank_);
    AddLevel("Set",nullptr,SetInput_,nullptr,SetRRender_);
    AddLevel("Waiting",InitWaiting_,InputWaiting_,UpdateWaiting_,RenderWaiting_);

    SetDefaultLevel("Menu");
}

void LevelManager::SetDefaultLevel(const std::string& LevelName) {
    CurrentLevel = GetLevelByName(LevelName);
}

Level LevelManager::GetLevelByName(const std::string& LevelName) {
    return this -> LevelMap.find(LevelName)->second;
}

void LevelManager::AddLevel(const std::string& LevelName,const std::function<void()>& Init,const std::function<void()>& Input,const std::function<void()>& Update,const std::function<void()>& Render) {
    Level temp(LevelName,Init,Input,Update,Render);
    LevelMap.insert({LevelName,temp});
}

void LevelManager::ChangeLevel(const std::string& LevelName) {
    CurrentLevel = GetLevelByName(LevelName);
}
