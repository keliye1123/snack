#pragma once
#include"../basic.h"
#include <iostream>
#include"../World.h"

inline void InitMap1_() {

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

        mainWorld.LocalSnack -> InitSnack_();
        InitFood_();

}

inline void InPutMap1_() {
    if (GetAsyncKeyState('A') && mainWorld.LocalSnack -> GetDir_() != RIGHT) mainWorld.LocalSnack -> SetDir_(LEFT);
    else if (GetAsyncKeyState('W') && mainWorld.LocalSnack -> GetDir_() != DOWN) mainWorld.LocalSnack -> SetDir_(UP);
    else if (GetAsyncKeyState('D') && mainWorld.LocalSnack -> GetDir_() != LEFT) mainWorld.LocalSnack -> SetDir_(RIGHT);
    else if (GetAsyncKeyState('S') && mainWorld.LocalSnack -> GetDir_() != UP) mainWorld.LocalSnack -> SetDir_(DOWN);
}

inline void  UpdateSnack1_() {
    Node* new_head  = new Node();

    switch (mainWorld.LocalSnack -> GetDir_()) {
        case LEFT:new_head -> x = mainWorld.LocalSnack -> GetHead() -> next -> x - SIZE;
            new_head -> y = mainWorld.LocalSnack -> GetHead() -> next -> y;
            break;

        case UP:new_head -> y = mainWorld.LocalSnack -> GetHead() -> next -> y - SIZE;
            new_head -> x = mainWorld.LocalSnack -> GetHead() -> next -> x;
            break;

        case RIGHT:new_head -> x = mainWorld.LocalSnack -> GetHead() -> next -> x + SIZE;
            new_head -> y = mainWorld.LocalSnack -> GetHead() -> next -> y;
            break;

        case DOWN:new_head -> y = mainWorld.LocalSnack -> GetHead() -> next -> y + SIZE;
            new_head -> x = mainWorld.LocalSnack -> GetHead() -> next -> x;
            break;
    }

    new_head -> next = mainWorld.LocalSnack -> GetHead() -> next;
    mainWorld.LocalSnack -> GetHead() -> next = new_head;

    Node* temp = mainWorld.LocalSnack -> GetHead() -> next;
    while (temp -> next != nullptr) {
        map[temp -> next ->y/SIZE][temp -> next -> x/SIZE] = false;
        temp = temp -> next;
    }

    if (F -> exists == true) {
        Node* pre = mainWorld.LocalSnack -> GetHead();
        Node* delete_tail = mainWorld.LocalSnack -> GetHead() -> next;
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
        //逻辑更新
        UpdateSnack1_();
        UpdateFood_();
        if (IsDead_()) {
            mainWorld.levelManager -> SetChangeLevel("End");
            mainWorld.levelManager -> SetFlag_(true);
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
    //渲染
    DrawBackground1_();
    DrawSnack_();
    DrawFood_();
    DrawScore_();
}




