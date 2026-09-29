#pragma once
#include "Level.h"
#include <string>

class LevelManager {
    //属性
    Level CurrentLevel;
    std::unordered_map<std::string,Level> LevelMap;
    bool Exchange_Flag;
    std::string changeLevel;

    //方法
public:
    LevelManager();

    Level GetLevelByName(const std::string& LevelName);

    void AddLevel(const std::string& LevelName,const std::function<void()>& Init,const std::function<void()>& Input,const std::function<void()>& Update,const std::function<void()>& Render);

    void ChangeLevel();

    void RunInit_();

    void RunInput_();

    void RunUpdate_();

    void RunRender_();

    Level GetCurrentLevel();

    [[nodiscard]] bool GetFlag_() const {
        return Exchange_Flag;
    }

    void SetFlag_(const bool& flag) {
        Exchange_Flag = flag;
    }

    void SetChangeLevel(const std::string& LevelName) {
        changeLevel = LevelName;
    }

    std::string GetCurrentLevelName() {
        return CurrentLevel.GetCurrentLevelName();
    }

};



