

#include "LeaderBoard.h"

#include <iostream>

#include "../Macro.h"
#include "../World.h"

LeaderBoard::LeaderBoard() {
    LevelFlag = {};
    len1 = 0;
    len2 = 0;
    ReadFile_();
}

void LeaderBoard::SetLevelFlag(const std::string& LevelFlag) {
    this -> LevelFlag = LevelFlag;
}

std::string LeaderBoard::GetLevelFlag() {
    return LevelFlag;
}
void LeaderBoard::BubbleSort(players players_[],int len)
{
    for (int i = len; i > 1; i--)
    {
        bool swapped = false;

        for (int j = 0; j + 1 < i; j++)
        {
            if (players_[j].score < players_[j + 1].score)
            {
                players temp = players_[j];
                players_[j] = players_[j + 1];
                players_[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;

    }
}

//更新
void LeaderBoard::RenderLeaderUpdate_() {
    if (LevelFlag == "Map1") {
        if (len1 <= 4){
            players1[len1].name = mainWorld.LocalSnack -> GetName_();
            players1[len1].score = mainWorld.LocalSnack -> GetScore_();
            len1++;
        }
        else if (mainWorld.LocalSnack -> GetScore_() > players1[len1 - 1].score){
            players1[len1 - 1].name = mainWorld.LocalSnack -> GetName_();
            players1[len1 - 1].score = mainWorld.LocalSnack -> GetScore_();
        }
        BubbleSort(players1,len1);
    }
    else if (LevelFlag == "Map2") {
        if (len2 <= 4) {
            players2[len2].name = mainWorld.LocalSnack -> GetName_();
            players2[len2].score = mainWorld.LocalSnack -> GetScore_();
            len2++;
        }
        else if (mainWorld.LocalSnack -> GetScore_() > players2[len2 - 1].score) {
            players2[len2 - 1].name = mainWorld.LocalSnack -> GetName_();
            players2[len2 - 1].score = mainWorld.LocalSnack -> GetScore_();
        }

        BubbleSort(players2,len2);

    }
}

//读取文件排行榜
void LeaderBoard::ReadFile_() {

    std::ifstream ifs("rank.txt",std::ios::in);

    //文件不存在
    if (!ifs.is_open()) {
        std::ofstream ofs("rank.txt",std::ios::out);
        ifs.open("rank.txt",std::ios::in);
        return;
    }

    std::string temp1;
    ifs >> temp1;
    len1 = stoi(temp1);
    ifs >> temp1;
    len2 = stoi(temp1);
    for (int i=0;i<len1;i++) {
        ifs >> temp1;
        players1[i].name = temp1;
        ifs >> temp1;
        players1[i].score = stoi(temp1);
    }
    for (int i=0;i<len2;i++) {
        ifs >> temp1;
        players2[i].name = temp1;
        ifs >> temp1;
        players2[i].score = stoi(temp1);
    }
    ifs.close();
}

//文件写入
void LeaderBoard::WriteFile_() const{

    std::ofstream ofs("rank.txt",std::ios::out);

    ofs << len1 << std::endl;
    ofs << len2 << std::endl;

    for (int i=0;i<len1;i++) {
        ofs << players1[i].name <<std::endl;
        ofs << players1[i].score<< std::endl;
    }
    for (int i=0;i<len2;i++) {
        ofs << players2[i].name <<std::endl;
        ofs << players2[i].score<< std::endl;
    }

    ofs.close();
}

//渲染排行榜
void LeaderBoard::RenderLeaderBoard_() {
    settextstyle(100,0,"微软雅黑");
    outtextxy(300,10,"排行榜");

    settextstyle(50,0,"微软雅黑");
    outtextxy(150,150,"围城模式");
    settextstyle(50,0,"微软雅黑");
    outtextxy(500,150,"无限模式");
    for (int i=0;i<len1;i++) {
        char pl1[10];
        sprintf(pl1,"%d.%s %d",i+1,players1[i].name.data(),players1[i].score);
        outtextxy(150,150 + i*50+50,pl1);
    }
    for (int i=0;i<len2;i++) {
        char pl2[10];
        sprintf(pl2,"%d.%s %d",i+1,players2[i].name.data(),players2[i].score);
        outtextxy(500,150 + i*50+50,pl2);
    }
}
