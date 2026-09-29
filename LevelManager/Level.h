#pragma once

#include <functional>
#include <string>

class Level {
    //属性
    std::string LevelName;
    std::function<void()> InitLevel;
    std::function<void()> InputLevel;
    std::function<void()> UpdateLevel;
    std::function<void()> RenderLevel;

    //方法
public:
    Level(const std::string& LevelName,const std::function<void()>& Init,const std::function<void()>& Input,const std::function<void()>& Update,const std::function<void()>& Render);

    void AddInitLevel_(const std::function<void()>& Init);

    void AddInputLevel_(const std::function<void()>& Input);

    void AddUpdateLevel_(const std::function<void()>& Update);

    void AddRenderLevel_(const std::function<void()>& Render);
};


