#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "basic.h"

inline void ReadFile_() {

    std::wifstream ifs(L"rank.txt",std::ios::in);

    //文件不存在
    if (!ifs.is_open()) {
        std::wofstream ofs(L"rank.txt",std::ios::out);
        ofs << len1 << std::endl;
        ofs << len2 << std::endl;
        ifs.open(L"rank.txt",std::ios::in);
    }

    std::wstring temp1;
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

inline void WriteFile_() {

    std::wofstream ofs("rank.txt",std::ios::out);

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