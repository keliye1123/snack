
#include "Snack.h"
#include "../Macro.h"
#include "../World.h"

Snack::Snack() {
    this -> speed = SPEED;
    this -> maxSpeed = MAXSPEED;
    this -> minSpeed = MINSPEED;
    this -> gap = 0;
    this ->score = 0;
    this -> dir = ORIGIN_DIRECTION;
    this -> Head = nullptr;
}

//控制蛇
void Snack::ControlSnack_() {
    if (GetAsyncKeyState('A') && this -> dir != RIGHT) this -> dir = LEFT;
    else if (GetAsyncKeyState('W') && this -> dir != DOWN) this -> dir = UP;
    else if (GetAsyncKeyState('D') && this -> dir != LEFT) this -> dir = RIGHT;
    else if (GetAsyncKeyState('S') && this -> dir != UP) this -> dir = DOWN;
}

//更新蛇
void Snack::UpdateSnack_() const{
    Node* new_head  = new Node();

    switch (this -> dir) {
        case LEFT:new_head -> x = this -> Head -> next -> x - SIZE;
            new_head -> y = this -> Head -> next -> y;
            break;

        case UP:new_head -> y = this -> Head -> next -> y - SIZE;
            new_head -> x = this -> Head -> next -> x;
            break;

        case RIGHT:new_head -> x = this -> Head -> next -> x + SIZE;
            new_head -> y = this -> Head -> next -> y;
            break;

        case DOWN:new_head -> y = this -> Head -> next -> y + SIZE;
            new_head -> x = this -> Head -> next -> x;
            break;
    }

    new_head -> next = this -> Head -> next;
    this -> Head -> next = new_head;

    Node* temp = this -> Head -> next;
    while (temp -> next != nullptr) {
        mainWorld.map[temp -> next ->y/SIZE][temp -> next -> x/SIZE] = false;
        temp = temp -> next;
    }

    if (mainWorld.LocalFood -> GetExists_() == true) {
        Node* pre = this -> Head;
        Node* delete_tail = this -> Head -> next;
        while (delete_tail -> next != nullptr) {
            delete_tail = delete_tail -> next;
            pre = pre -> next;
        }
        mainWorld.map[delete_tail -> y/SIZE][delete_tail -> x/SIZE] = true;
        free(delete_tail);
        pre -> next = nullptr;

    }
}

void Snack::UpdateSnack2_() {
    Node* new_head  = new Node;

    switch (this -> dir) {
        case LEFT:new_head -> x = this -> Head -> next -> x - SIZE;
            new_head -> y = this -> Head -> next -> y;
            if (new_head -> x < 0) {
                new_head -> x = WIDTH - SIZE;
            }
            break;

        case UP:new_head -> y = this -> Head -> next -> y - SIZE;
            new_head -> x = this -> Head -> next -> x;
            if (new_head -> y < 0) {
                new_head -> y = HEIGHT - SIZE;
            }
            break;

        case RIGHT:new_head -> x = this -> Head -> next -> x + SIZE;
            new_head -> y = this -> Head -> next -> y;
            if (new_head -> x > WIDTH - SIZE) {
                new_head -> x = 0;
            }
            break;

        case DOWN:new_head -> y = this -> Head -> next -> y + SIZE;
            new_head -> x = this -> Head -> next -> x;
            if (new_head -> y > HEIGHT - SIZE) {
                new_head -> y = 0;
            }
            break;
    }

    new_head -> next = this -> Head -> next;
    this -> Head -> next = new_head;

    Node* temp = this -> Head -> next;
    while (temp -> next != nullptr) {
        mainWorld.map[temp -> next ->y/SIZE][temp -> next -> x/SIZE] = false;
        temp = temp -> next;
    }

    if (mainWorld.LocalFood -> GetExists_() == true) {
        Node* pre = this -> Head;
        Node* delete_tail = this -> Head -> next;
        while (delete_tail -> next != nullptr) {
            delete_tail = delete_tail -> next;
            pre = pre -> next;
        }
        mainWorld.map[delete_tail -> y/SIZE][delete_tail -> x/SIZE] = true;
        free(delete_tail);
        pre -> next = nullptr;

    }

}

void Snack::SetGap_(int gap_) {
    this -> gap = gap_;
}

int Snack::GetGap_() const{
    return this -> gap;
}

//初始化蛇
void Snack::InitSnack_() {
    this -> gap = speed;
    this ->name.clear();
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

void Snack::SetName_(std::string name_) {
    this -> name = name_;
}

std::string& Snack::GetName_(){
    return this -> name;
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

bool Snack::IsDead_() const{
    if (mainWorld.map[Head -> next-> y/SIZE][Head -> next-> x/SIZE] == false) {
        Node* cur = Head;
        while (cur != nullptr) {
            Node* next = cur->next;
            free(cur);
            cur = next;
        }
        return true;
    }
    return false;
}

//渲染蛇
void Snack::DrawSnack_() const{
    Node* head = Head -> next;
    while (head != nullptr) {

        setfillcolor(BLUE);
        fillrectangle(head -> x,head -> y,head -> x + SIZE,head -> y+ SIZE);
        head = head -> next;
    }
}

void Snack::DrawScore_() const{
    char s[20];
    sprintf(s,"得分：%d",score);
    settextstyle(75,0,"微软雅黑");
    outtextxy(0,HEIGHT,s);
}