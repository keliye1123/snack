#pragma once
#include "Level.h"
#include <string>

class LevelManager {
    //属性
    Level CurrentLevel;
    std::unordered_map<std::string,Level> LevelMap;

    //方法
    LevelManager();

    void SetDefaultLevel(const std::string& LevelName);

    Level GetLevelByName(const std::string& LevelName);

    void AddLevel(const std::string& LevelName,const std::function<void()>& Init,const std::function<void()>& Input,const std::function<void()>& Update,const std::function<void()>& Render);

    void ChangeLevel(const std::string& LevelName);


};



