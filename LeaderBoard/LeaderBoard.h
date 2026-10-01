#pragma once
#include <string>
#include <fstream>

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
    int len1;
    int len2;
    std::string LevelFlag;

    //方法
private:
    //排序
    void BubbleSort(players players_[],int len);

public:
    LeaderBoard();

    void SetLevelFlag(const std::string& LevelFlag);

    std::string GetLevelFlag();

    //更新
    void RenderLeaderUpdate_();

    //读取文件排行榜
    void ReadFile_();

    //文件写入
    void WriteFile_() const;

    //渲染排行榜
    void RenderLeaderBoard_();

};


