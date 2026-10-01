#pragma once

#include <string>
//蛇节点定义
typedef struct snack {
    int x;
    int y;
    struct snack *next;
}Node;

//方向类型枚举
enum Direction {
    LEFT,//0
    UP,//1
    RIGHT,//2
    DOWN//3
};


class Snack {
    //属性
    int speed;                  //速度,speed表示每隔多少帧更新一次，所以speed越小速度越快
    int maxSpeed;               //最大速度
    int minSpeed;               //最小速度
    int gap;                    //当前处于第几帧
    std::string name;           //当前蛇的名字
    int score;                  //分数
    Direction dir;              //蛇的方向
    Node* Head;                 //蛇的头节点

    //方法
public:
    Snack();

    //控制蛇
    void ControlSnack_();

    //更新蛇
    void UpdateSnack_() const;

    //无尽模式下更新蛇
    void UpdateSnack2_();

    //初始化蛇的节点，分数和方向和名字
    void InitSnack_();

    int GetMaxSpeed_() const{
        return maxSpeed;
    }

    int GetMinSpeed_() const{
        return minSpeed;
    }

    void SetGap_(int gap_);

    [[nodiscard]] int GetGap_() const;

    void SetName_(std::string name_);

    [[nodiscard]] std::string& GetName_();

    //修改分数
    void SetScore_(const int& score);

    //得到蛇的分数
    [[nodiscard]] int GetScore_() const;

    //修改速度
    void SetSpeed_(const int& speed);

    //得到速度
    [[nodiscard]] int GetSpeed_() const;

    //修改方向
    void SetDir_(Direction dir);

    //获得方向
    [[nodiscard]] Direction GetDir_() const;

    //获取头节点
    [[nodiscard]] Node* GetHead() const;

    //判断蛇在当前对局中是否死亡
    [[nodiscard]] bool IsDead_() const;

    //渲染蛇
    void DrawSnack_() const;

    //渲染分数
    void DrawScore_() const;
};


