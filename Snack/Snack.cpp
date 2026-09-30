
#include "Snack.h"

Snack::Snack() {
    this -> speed = SPEED;
    this ->score = 0;
    this -> dir = ORIGIN_DIRECTION;
    this -> Head = nullptr;
}

//初始化蛇
void Snack::InitSnack_() {
    this ->score = 0;
    this -> dir = ORIGIN_DIRECTION;
    Head = new Node();

    Node* head = new Node();
    Node* mid  = new Node();
    Node* tail = new Node();

    head->next = mid;
    mid->next = tail;
    tail->next = nullptr;

    head -> x = HEAD_POSITION_X;
    head -> y = HEAD_POSITION_Y;

    dir = ORIGIN_DIRECTION;
    score = 0;

    switch (dir) {
        case LEFT: mid -> x = HEAD_POSITION_X + SIZE;
            mid -> y = HEAD_POSITION_Y;
            tail -> x = HEAD_POSITION_X + SIZE*2;
            tail -> y = HEAD_POSITION_Y;
            break;

        case UP:   mid -> x = HEAD_POSITION_X;
            mid -> y = HEAD_POSITION_Y + SIZE;
            tail -> x = HEAD_POSITION_X;
            tail -> y = HEAD_POSITION_Y + SIZE*2;
            break;


        case RIGHT:mid -> x = HEAD_POSITION_X - SIZE;
            mid -> y = HEAD_POSITION_Y;
            tail -> x = HEAD_POSITION_X - SIZE*2;
            tail -> y = HEAD_POSITION_Y;
            break;

        case DOWN: mid -> x = HEAD_POSITION_X;
            mid -> y = HEAD_POSITION_Y - SIZE;
            tail -> x = HEAD_POSITION_X;
            tail -> y = HEAD_POSITION_Y - SIZE*2;
            break;
    }
    Head -> next =  head;
}

//修改分数
void Snack::SetScore_(const int& score_) {
    this -> score = score_;
}

//得到蛇的分数
int Snack::GetScore_() const{
    return this -> score;
}

//修改速度
void Snack::SetSpeed_(const int& speed_) {
    this -> speed = speed_;
}

//得到速度
int Snack::GetSpeed_() const{
    return this -> speed;
}

//修改方向
void Snack::SetDir_(Direction dir_) {
    this -> dir = dir_;
}

//获得方向
Direction Snack::GetDir_() const{
    return this -> dir;
}

Node* Snack::GetHead() const{
    return this -> Head;
}

bool Snack::IsDead_() {
    if (map[Head -> next-> y/SIZE][Head -> next-> x/SIZE] == false) {
        Node* cur = Head;
        while (cur != nullptr) {
            Node* next = cur->next;
            free(cur);
            cur = next;
        }
        free(F);
        return true;
    }
    return false;
}

//渲染蛇
void Snack::DrawSnack_() {
    Node* head = Head -> next;
    while (head != nullptr) {

        setfillcolor(BLUE);
        fillrectangle(head -> x,head -> y,head -> x + SIZE,head -> y+ SIZE);
        head = head -> next;
    }
}