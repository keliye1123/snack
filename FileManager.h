#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "basic.h"

inline void ReadFile_() {

    std::ifstream ifs("rank.txt",std::ios::in);

    //文件不存在
    if (!ifs.is_open()) {
        std::ofstream ofs("rank.txt",std::ios::out);
        ofs << len1 << std::endl;
        ofs << len2 << std::endl;
        ifs.open("rank.txt",std::ios::in);
    }

    char temp1[1024];
    ifs >> temp1;
    len1 = atoi(temp1);
    ifs >> temp1;
    len2 = atoi(temp1);
    for (int i=0;i<len1;i++) {
        ifs >> temp1;
        strcpy(players1[i].name,temp1);
        ifs >> temp1;
        players1[i].score = atoi(temp1);
    }
    for (int i=0;i<len2;i++) {
        ifs >> temp1;
        strcpy(players2[i].name,temp1);
        ifs >> temp1;
        players2[i].score = atoi(temp1);
    }

    ifs.close();
}

inline void WriteFile_() {

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