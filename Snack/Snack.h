#pragma once

#include "../Macro.h"

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
    int speed;                  //速度
    int score;                  //分数
    Direction dir;              //蛇的方向
    Node* Head;                 //蛇的头节点

    //方法
public:
    Snack();

    //初始化蛇的节点，分数和方向
    void InitSnack_();

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
    bool IsDead_();

    //渲染蛇
    void DrawSnack_();
};


