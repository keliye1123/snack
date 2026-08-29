#pragma once
#include"../basic.h"
#include <iostream>

inline void InitMap1_() {
    if (exchange_level_flag == true) {
        for (int i = 0;i <= HEIGHT/SIZE-1;i++ ) {
            for (int j = 0;j <= WIDTH/SIZE-1;j++ ) {
                map[i][j] = true;
            }
        }
        for (int j = 0;j <= WIDTH/SIZE-1;j++ ) {
            map[0][j] = false;
            map[HEIGHT/SIZE-1][j] = false;
        }
        for (int j = 0;j <= HEIGHT/SIZE-1;j++ ) {
            map[j][0] = false;
            map[j][WIDTH/SIZE-1] = false;
        }

        InitSnack_();
        InitFood_();

        exchange_level_flag = false;
    }
}

inline void InPutMap1_() {
    if (GetAsyncKeyState('A') && dir != RIGHT) {
        dir = LEFT;
    }
    else if (GetAsyncKeyState('W') && dir != DOWN) {
        dir = UP;
    }
    else if (GetAsyncKeyState('D') && dir != LEFT) {
        dir = RIGHT;
    }
    else if (GetAsyncKeyState('S') && dir != UP) {
        dir = DOWN;
    }
}

inline void  UpdateSnack1_() {
    Node* new_head  = new Node();

    switch (dir) {
        case LEFT:new_head -> x = S -> next -> x - SIZE;
            new_head -> y = S -> next -> y;
            break;

        case UP:new_head -> y = S -> next -> y - SIZE;
            new_head -> x = S -> next -> x;
            break;

        case RIGHT:new_head -> x = S -> next -> x + SIZE;
            new_head -> y = S -> next -> y;
            break;

        case DOWN:new_head -> y = S -> next -> y + SIZE;
            new_head -> x = S -> next -> x;
            break;
    }

    new_head -> next = S -> next;
    S -> next = new_head;

    Node* temp = S -> next;
    while (temp -> next != nullptr) {
        map[temp -> next ->y/SIZE][temp -> next -> x/SIZE] = false;
        temp = temp -> next;
    }

    if (F -> exists == true) {
        Node* pre = S;
        Node* delete_tail = S -> next;
        while (delete_tail -> next != nullptr) {
            delete_tail = delete_tail -> next;
            pre = pre -> next;
        }
        map[delete_tail -> y/SIZE][delete_tail -> x/SIZE] = true;
        free(delete_tail);
        pre -> next = nullptr;

    }

}

inline void UpdateMap1_() {
    if (speed_gap == speed) {
        speed_gap = 0;
        //Âß¼­¸üÐÂ
        UpdateSnack1_();
        UpdateFood_();
        if (IsDead_()) {
            before_level = 1;
            cur_level = 2;
            exchange_level_flag = true;
            return;
        }
    }else {
        speed_gap++;
    }
}

inline void DrawBackground1_() {
    setfillcolor(BLACK);
    fillrectangle(0,0,SIZE,HEIGHT);
    fillrectangle(0,0,WIDTH,SIZE);
    fillrectangle(0,HEIGHT - SIZE,WIDTH,HEIGHT);
    fillrectangle(WIDTH - SIZE,0,WIDTH,HEIGHT);

    setlinecolor(WHITE);
    setlinestyle(PS_SOLID,2);
    for (int i = 0;i*SIZE <= WIDTH;i++ ) {

        line(i*SIZE,0,i*SIZE,750);
    }
    for (int j = 0;j*SIZE <= HEIGHT;j++) {
        line(0,j*SIZE,900,j*SIZE);
    }
}

inline void RenderMap1_() {
    //äÖÈ¾
    DrawBackground1_();
    DrawSnack_();
    DrawFood_();
    DrawScore_();
}




