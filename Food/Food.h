#pragma once

class Food {
    //属性
private:
    int x;
    int y;
    bool exists;

    //方法
public:
    Food();

    void SetExists_(const bool& flag);

    bool GetExists_() const;

    //初始化食物
    void InitFood_();

    //更新食物
    void UpdateFood_();

    //渲染食物
    void DrawFood_() const;
};

