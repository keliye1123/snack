#pragma once
#include "../basic.h"

inline char s[10];
inline char name[10] = {};
inline int index = 0;

inline void WriteScore_() {

    if (before_level == 1) {

        if (len1 <= 4){
            strcpy(players1[len1].name,name);
            players1[len1].score = score;
            len1++;
        }
        else if (score > players1[len1 - 1].score){
            strcpy(players1[len1 - 1].name,name);
            players1[len1 - 1].score = score;
        }
        std::cout << "≈≈–Ú«∞ len1 = " << len1 << ", MAX_PLAYERS = " << MAX_PLAYERS << std::endl;
        BubbleSort(players1,len1);

    }
    else if (before_level == 3) {

        if (len2 <= 4) {
            strcpy(players2[len2].name,name);
            players2[len2].score = score;
            len2++;
        }
        else if (score > players2[len2 - 1].score) {
            strcpy(players2[len2 - 1].name,name);
            players2[len2 - 1].score = score;
        }

        BubbleSort(players2,len2);

    }

}

inline void InitEnd_() {
    if (exchange_level_flag == true) {

        memset(s,0,sizeof(s));
        memset(name,0,sizeof(name));
        index = 0;
        sprintf(s,"%d",score);
        std::cout << name << std::endl;

        exchange_level_flag = false;
    }

}

inline void InputEnd_() {
     //º‡≤‚ ‰»Î
        if (index >= 8) {index = 8;}
        else if (GetAsyncKeyState('A') & 0x8000) { name[index++] = 'A'; }
        else if (GetAsyncKeyState('B') & 0x8000) { name[index++] = 'B'; }
        else if (GetAsyncKeyState('C') & 0x8000) { name[index++] = 'C'; }
        else if (GetAsyncKeyState('D') & 0x8000) { name[index++] = 'D'; }
        else if (GetAsyncKeyState('E') & 0x8000) { name[index++] = 'E'; }
        else if (GetAsyncKeyState('F') & 0x8000) { name[index++] = 'F'; }
        else if (GetAsyncKeyState('G') & 0x8000) { name[index++] = 'G'; }
        else if (GetAsyncKeyState('H') & 0x8000) { name[index++] = 'H'; }
        else if (GetAsyncKeyState('I') & 0x8000) { name[index++] = 'I'; }
        else if (GetAsyncKeyState('J') & 0x8000) { name[index++] = 'J'; }
        else if (GetAsyncKeyState('K') & 0x8000) { name[index++] = 'K'; }
        else if (GetAsyncKeyState('L') & 0x8000) { name[index++] = 'L'; }
        else if (GetAsyncKeyState('M') & 0x8000) { name[index++] = 'M'; }
        else if (GetAsyncKeyState('N') & 0x8000) { name[index++] = 'N'; }
        else if (GetAsyncKeyState('O') & 0x8000) { name[index++] = 'O'; }
        else if (GetAsyncKeyState('P') & 0x8000) { name[index++] = 'P'; }
        else if (GetAsyncKeyState('Q') & 0x8000) { name[index++] = 'Q'; }
        else if (GetAsyncKeyState('R') & 0x8000) { name[index++] = 'R'; }
        else if (GetAsyncKeyState('S') & 0x8000) { name[index++] = 'S'; }
        else if (GetAsyncKeyState('T') & 0x8000) { name[index++] = 'T'; }
        else if (GetAsyncKeyState('U') & 0x8000) { name[index++] = 'U'; }
        else if (GetAsyncKeyState('V') & 0x8000) { name[index++] = 'V'; }
        else if (GetAsyncKeyState('W') & 0x8000) { name[index++] = 'W'; }
        else if (GetAsyncKeyState('X') & 0x8000) { name[index++] = 'X'; }
        else if (GetAsyncKeyState('Y') & 0x8000) { name[index++] = 'Y'; }
        else if (GetAsyncKeyState('Z') & 0x8000) { name[index++] = 'Z'; }
        else if (GetAsyncKeyState('0') & 0x8000) { name[index++] = '0'; }
        else if (GetAsyncKeyState('1') & 0x8000) { name[index++] = '1'; }
        else if (GetAsyncKeyState('2') & 0x8000) { name[index++] = '2'; }
        else if (GetAsyncKeyState('3') & 0x8000) { name[index++] = '3'; }
        else if (GetAsyncKeyState('4') & 0x8000) { name[index++] = '4'; }
        else if (GetAsyncKeyState('5') & 0x8000) { name[index++] = '5'; }
        else if (GetAsyncKeyState('6') & 0x8000) { name[index++] = '6'; }
        else if (GetAsyncKeyState('7') & 0x8000) { name[index++] = '7'; }
        else if (GetAsyncKeyState('8') & 0x8000) { name[index++] = '8'; }
        else if (GetAsyncKeyState('9') & 0x8000) { name[index++] = '9'; }
        if (GetAsyncKeyState(VK_BACK) & 0x8000) {if (index > 0){ index--,name[index] = '\0';}};
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            name[index] = '\0';
            WriteScore_();
            cur_level = 0;
            exchange_level_flag = true;
            return;
        }

}

inline void RenderEnd_() {
    settextstyle(50,20,"Œ¢»Ì—≈∫⁄");
    outtextxy(200,300,"◊Ó÷’µƒ∑÷£∫");
    outtextxy(400,300,s);
    outtextxy(200,400," ‰»ÎÍ«≥∆£∫");
    outtextxy(400,400,name);
}


