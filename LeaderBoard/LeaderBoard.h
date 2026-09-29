#pragma once
#include <string>

#define  MAX_PLAYERS 5          //排行榜最大人数

typedef struct people {
    std::string name;//MAXSIZE = 10
    int  score = 0;
}players;

class LeaderBoard {
    //属性
private:
    players players1[MAX_PLAYERS];
    players players2[MAX_PLAYERS];

    //方法
private:
    //排序
    void BubbleSort(players players_[],int len);

public:


};


