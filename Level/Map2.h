#pragma once
#include "../basic.h"

inline void InitMap2_() {
    if (exchange_level_flag == true) {

        for (int i = 0;i <= HEIGHT/SIZE-1;i++ ) {
            for (int j = 0;j <= WIDTH/SIZE-1;j++ ) {
                map[i][j] = true;
            }
        }

        InitSnack_();
        InitFood_();

        exchange_level_flag = false;

    }

}

inline void InPutMap2_() {
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

//地图2蛇的移动逻辑
inline void  UpdateSnack2_() {
    Node* new_head  = new Node;

    switch (dir) {
        case LEFT:new_head -> x = S -> next -> x - SIZE;
            new_head -> y = S -> next -> y;
            if (new_head -> x < 0) {
                new_head -> x = WIDTH - SIZE;
            }
            break;

        case UP:new_head -> y = S -> next -> y - SIZE;
            new_head -> x = S -> next -> x;
            if (new_head -> y < 0) {
                new_head -> y = HEIGHT - SIZE;
            }
            break;

        case RIGHT:new_head -> x = S -> next -> x + SIZE;
            new_head -> y = S -> next -> y;
            if (new_head -> x > WIDTH - SIZE) {
                new_head -> x = 0;
            }
            break;

        case DOWN:new_head -> y = S -> next -> y + SIZE;
            new_head -> x = S -> next -> x;
            if (new_head -> y > HEIGHT - SIZE) {
                new_head -> y = 0;
            }
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

inline void UpdateMap2_() {
    if (speed_gap == speed) {
        speed_gap = 0;
        //逻辑更新
        UpdateSnack2_();
        UpdateFood_();
        if (IsDead_()) {
            before_level = 3;
            cur_level = 2;
            exchange_level_flag = true;
            return;
        }
    }else {
        speed_gap++;
    }
}

//渲染背景2
inline void DrawBackground2_() {

    setlinecolor(WHITE);
    setlinestyle(PS_SOLID,2);
    for (int i = 0;i*SIZE <= WIDTH;i++ ) {

        line(i*SIZE,0,i*SIZE,750);
    }
    for (int j = 0;j*SIZE <= HEIGHT;j++) {
        line(0,j*SIZE,900,j*SIZE);
    }
}

inline void RenderMap2_() {
    DrawBackground2_();
    DrawSnack_();
    DrawFood_();
    DrawScore_();
}