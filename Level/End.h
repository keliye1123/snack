#pragma once
#include "../basic.h"
#include "../InputMethod/InputMethod.h"

inline char s[10];
inline std::string name;//宽字符字符串
inline std::vector<Word> words;

inline bool key_lock = false;

inline void WriteScore_() {

    if (before_level == 1) {

        if (len1 <= 4){
            players1[len1].name = name;
            players1[len1].score = score;
            len1++;
        }
        else if (score > players1[len1 - 1].score){
            players1[len1 - 1].name = name;
            players1[len1 - 1].score = score;
        }
        BubbleSort(players1,len1);

    }
    else if (before_level == 3) {

        if (len2 <= 4) {
            players2[len2].name = name;
            players2[len2].score = score;
            len2++;
        }
        else if (score > players2[len2 - 1].score) {
            players2[len2 - 1].name = name;
            players2[len2 - 1].score = score;
        }

        BubbleSort(players2,len2);

    }

}

inline void InitEnd_() {
    if (exchange_level_flag == true) {

        memset(s,0,sizeof(s));
        name.clear();
        sprintf(s,"%d",score);
        exchange_level_flag = false;
    }

}

inline void InputEnd_() {
     //监测输入
    peekmessage(&msg, EM_KEY);
    if (msg.message == WM_KEYDOWN && !key_lock) {
        key_lock = true;

        //未处于输入法时回车：完成输入并退出
        if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && inputMethod.GetStatus_() == false) {
            WriteScore_();
            cur_level = 0;
            exchange_level_flag = true;
            return;
        }

        words = inputMethod.RunInputMethod_(name);
    }
    else if (msg.message == WM_KEYUP && key_lock) key_lock = false;

}

inline void RenderEnd_() {
    inputMethod.Draw_();
    settextstyle(50,20,"微软雅黑");
    outtextxy(200,300,"最终的分：");
    outtextxy(400,300,s);
    outtextxy(200,400,"输入昵称：");
    outtextxy(400,400,name.c_str());
}


