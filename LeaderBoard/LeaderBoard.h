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

    //方法
private:
    //排序
    void BubbleSort(players players_[],int len);

public:
    LeaderBoard();

    //读取文件排行榜
    void ReadFile_() {

        std::ifstream ifs("rank.txt",std::ios::in);

        //文件不存在
        if (!ifs.is_open()) {
            std::ofstream ofs("rank.txt",std::ios::out);
            ofs << len1 << std::endl;
            ofs << len2 << std::endl;
            ifs.open("rank.txt",std::ios::in);
        }

        std::string temp1;
        ifs >> temp1;
        len1 = (int)temp1.size();
        ifs >> temp1;
        len2 = (int)temp1.size();
        for (int i=0;i<len1;i++) {
            ifs >> temp1;
            players1[i].name = temp1;
            ifs >> temp1;
            players1[i].score = (int)temp1.size();
        }
        for (int i=0;i<len2;i++) {
            ifs >> temp1;
            players2[i].name = temp1;
            ifs >> temp1;
            players2[i].score = (int)temp1.size();
        }

        ifs.close();
    }

    //文件写入
    void WriteFile_() {

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

};


