#pragma once
#include <ranges>

#include "basic.h"
#pragma comment(lib,"ws2_32.lib")
#define SPORT 5005//服务器端口号

inline void ConnectToServer_() {

}

inline void InitSnack1_() {
    player1_S = new Node();

    Node* head = new Node();
    Node* mid  = new Node();
    Node* tail = new Node();

    head->next = mid;
    mid->next = tail;
    tail->next = nullptr;

    head -> x = PLAYER1_HEAD_X;
    head -> y = PLAYER1_HEAD_Y;

    player1_dir = PLAYER1_DIRECTION;
    player1_score = 0;

    switch (player1_dir) {
        case LEFT: mid -> x = PLAYER1_HEAD_X + SIZE;
            mid -> y = PLAYER1_HEAD_Y;
            tail -> x = PLAYER1_HEAD_X + SIZE*2;
            tail -> y = PLAYER1_HEAD_Y;
            break;

        case UP:   mid -> x = PLAYER1_HEAD_X;
            mid -> y = PLAYER1_HEAD_Y + SIZE;
            tail -> x = PLAYER1_HEAD_X;
            tail -> y = PLAYER1_HEAD_Y + SIZE*2;
            break;


        case RIGHT:mid -> x = PLAYER1_HEAD_X - SIZE;
            mid -> y = PLAYER1_HEAD_Y;
            tail -> x = PLAYER1_HEAD_X - SIZE*2;
            tail -> y = PLAYER1_HEAD_Y;
            break;

        case DOWN: mid -> x = PLAYER1_HEAD_X;
            mid -> y = PLAYER1_HEAD_Y - SIZE;
            tail -> x = PLAYER1_HEAD_X;
            tail -> y = PLAYER1_HEAD_Y - SIZE*2;
            break;
    }
    player1_S -> next =  head;
}

inline void InitSnack2_() {
    player2_S = new Node();

    Node* head = new Node();
    Node* mid  = new Node();
    Node* tail = new Node();

    head->next = mid;
    mid->next = tail;
    tail->next = nullptr;

    head -> x = PLAYER2_HEAD_X;
    head -> y = PLAYER2_HEAD_Y;

    player2_dir = PLAYER2_DIRECTION;
    player2_score = 0;

    switch (player2_dir) {
        case LEFT: mid -> x = PLAYER2_HEAD_X + SIZE;
            mid -> y = PLAYER2_HEAD_Y;
            tail -> x = PLAYER2_HEAD_X + SIZE*2;
            tail -> y = PLAYER2_HEAD_Y;
            break;

        case UP:   mid -> x = PLAYER2_HEAD_X;
            mid -> y = PLAYER2_HEAD_Y + SIZE;
            tail -> x = PLAYER2_HEAD_X;
            tail -> y = PLAYER2_HEAD_Y + SIZE*2;
            break;


        case RIGHT:mid -> x = PLAYER2_HEAD_X - SIZE;
            mid -> y = PLAYER2_HEAD_Y;
            tail -> x = PLAYER2_HEAD_X - SIZE*2;
            tail -> y = PLAYER2_HEAD_Y;
            break;

        case DOWN: mid -> x = PLAYER2_HEAD_X;
            mid -> y = PLAYER2_HEAD_Y - SIZE;
            tail -> x = PLAYER2_HEAD_X;
            tail -> y = PLAYER2_HEAD_Y - SIZE*2;
            break;
    }
    player2_S -> next =  head;
}

inline bool TogetherIsDead_() {
    if (cur_player == 1) {
        if (map[player1_S -> next-> y/SIZE][player1_S -> next-> x/SIZE] == false) {
            Node* cur = player1_S;
            while (cur != nullptr) {
                Node* next = cur->next;
                delete cur;
                cur = next;
            }
            player1_S = nullptr;
            return true;
        }
    }
    else {
        if (map[player2_S -> next-> y/SIZE][player2_S -> next-> x/SIZE] == false) {
            Node* cur = S;
            while (cur != nullptr) {
                Node* next = cur->next;
                delete cur;
                cur = next;
            }
            player2_S = nullptr;
            return true;
        }
    }
   
    return false;
}

//玩家1的移动逻辑
inline void  UpdatePlay1_(int f_x,int f_y) {
    Node* new_head  = new Node;

    switch (player1_dir) {
        case LEFT:new_head -> x = player1_S -> next -> x - SIZE;
            new_head -> y = player1_S -> next -> y;
            if (new_head -> x < 0) {
                new_head -> x = WIDTH - SIZE;
            }
            break;

        case UP:new_head -> y = player1_S -> next -> y - SIZE;
            new_head -> x = player1_S -> next -> x;
            if (new_head -> y < 0) {
                new_head -> y = HEIGHT - SIZE;
            }
            break;

        case RIGHT:new_head -> x = player1_S -> next -> x + SIZE;
            new_head -> y = player1_S -> next -> y;
            if (new_head -> x > WIDTH - SIZE) {
                new_head -> x = 0;
            }
            break;

        case DOWN:new_head -> y = player1_S -> next -> y + SIZE;
            new_head -> x = player1_S -> next -> x;
            if (new_head -> y > HEIGHT - SIZE) {
                new_head -> y = 0;
            }
            break;
    }

    new_head -> next = player1_S -> next;
    player1_S -> next = new_head;

    Node* temp = player1_S -> next;
    while (temp -> next != nullptr) {
        map[temp -> next ->y/SIZE][temp -> next -> x/SIZE] = false;
        temp = temp -> next;
    }

    //玩家1未吃到食物
    if (!(player1_S -> next -> x == f_x && player1_S -> next -> y == f_y)) {
        //未吃到food尾巴减少
        Node* pre = player1_S;
        Node* delete_tail = player1_S -> next;
        while (delete_tail -> next != nullptr) {
            delete_tail = delete_tail -> next;
            pre = pre -> next;
        }
        map[delete_tail -> y/SIZE][delete_tail -> x/SIZE] = true;
        delete delete_tail;
        pre -> next = nullptr;
    }

}

//玩家2的移动逻辑
inline void UpdatePlay2_(int f_x,int f_y) {
    Node* new_head  = new Node;

    switch (player2_dir) {
        case LEFT:new_head -> x = player2_S -> next -> x - SIZE;
            new_head -> y = player2_S -> next -> y;
            if (new_head -> x < 0) {
                new_head -> x = WIDTH - SIZE;
            }
            break;

        case UP:new_head -> y = player2_S -> next -> y - SIZE;
            new_head -> x = player2_S -> next -> x;
            if (new_head -> y < 0) {
                new_head -> y = HEIGHT - SIZE;
            }
            break;

        case RIGHT:new_head -> x = player2_S -> next -> x + SIZE;
            new_head -> y = player2_S -> next -> y;
            if (new_head -> x > WIDTH - SIZE) {
                new_head -> x = 0;
            }
            break;

        case DOWN:new_head -> y = player2_S -> next -> y + SIZE;
            new_head -> x = player2_S -> next -> x;
            if (new_head -> y > HEIGHT - SIZE) {
                new_head -> y = 0;
            }
            break;
    }

    new_head -> next = player2_S -> next;
   player2_S -> next = new_head;

    Node* temp = player2_S -> next;
    while (temp -> next != nullptr) {
        map[temp -> next ->y/SIZE][temp -> next -> x/SIZE] = false;
        temp = temp -> next;
    }


    //玩家2未吃到食物
    if (!(player2_S -> next -> x == f_x && player2_S -> next -> y == f_y)) {
        //未吃到food尾巴减少
        Node* pre = player2_S;
        Node* delete_tail = player2_S -> next;
        while (delete_tail -> next != nullptr) {
            delete_tail = delete_tail -> next;
            pre = pre -> next;
        }
        map[delete_tail -> y/SIZE][delete_tail -> x/SIZE] = true;
        delete delete_tail;
        pre -> next = nullptr;
    }

}

//渲染玩家1
inline void DrawSnack1_() {
    Node* head = player1_S -> next;
    while (head != nullptr) {

        setfillcolor(BLUE);
        fillrectangle(head -> x,head -> y,head -> x + SIZE,head -> y+ SIZE);
        head = head -> next;
    }
}
//渲染玩家2
inline void DrawSnack2_() {
    Node* head = player2_S -> next;
    while (head != nullptr) {

        setfillcolor(GREEN);
        fillrectangle(head -> x,head -> y,head -> x + SIZE,head -> y+ SIZE);
        head = head -> next;
    }
}