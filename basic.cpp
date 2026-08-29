#include "basic.h"
#include <random>

int before_level = 0;
int cur_level = 0;
bool exchange_level_flag = true;
int level = 0;
int speed = 3;
int score = 0;
int len1 = 0;
int len2 = 0;

long long delta_time = 0;

Node* S = nullptr;
Food* F = nullptr;

Node* player1_S = nullptr;
Node* player2_S = nullptr;
int player1_score = 0;
int player2_score = 0;
Direction player1_dir = RIGHT;
Direction player2_dir = RIGHT;

ThreadPoll pool(3);

int cur_player = 0;
bool exchange_dir = false;

players players1[MAX_PLAYERS];
players players2[MAX_PLAYERS];

bool map[HEIGHT/SIZE][WIDTH/SIZE];//全局地图

Direction dir = RIGHT;//蛇的方向
POINT pt;

bool InArea_(int x1,int y1,int x2,int y2) {
    if (pt.x >= x1 and pt.x <= x2 && pt.y >= y1 and pt.y <= y2) {
        return true;
    }
    return false;
}

//声明随机数种子
std::random_device rd;
std::mt19937 gen(rd());

//获取随机数
int RandInt_(int lower,int upper) {
    if(lower > upper)
    {
        int temp = lower;
        lower = upper;
        upper = temp;
    }
    std::uniform_int_distribution<int> dis(lower, upper);
    return dis(gen);
}

void BubbleSort(players players_[],int len)
{
    for (int i = len; i > 1; i--)
    {
        bool swapped = false;

        for (int j = 0; j + 1 < i; j++)
        {
            if (players_[j].score < players_[j + 1].score)
            {
                players temp = players_[j];
                players_[j] = players_[j + 1];
                players_[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;

    }
}

//初始化蛇
void InitSnack_() {
    S = new Node();

    Node* head = (Node*)malloc(sizeof(Node));
    Node* mid  = (Node*)malloc(sizeof(Node));
    Node* tail = (Node*)malloc(sizeof(Node));

    head->next = mid;
    mid->next = tail;
    tail->next = NULL;

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
    S -> next =  head;
}

//食物初始化
void InitFood_() {
    Food* food = (Food*)malloc(sizeof(Food));
    do {
        food -> x = RandInt_(1,WIDTH/SIZE-2)*SIZE;
        food -> y = RandInt_(1,HEIGHT/SIZE-2)*SIZE;
    }while ((map[food ->y/SIZE][food -> x/SIZE] == false));

    food -> exists = true;
    F =  food;
}

void UpdateFood_() {
    if (S -> next -> x == F -> x && S -> next -> y == F -> y) {
        F -> exists = false;
        score += speed;
        return;
    }
    if (F -> exists ) return;

    do {
        F -> x = RandInt_(1,WIDTH/SIZE-2)*SIZE;
        F -> y = RandInt_(1,HEIGHT/SIZE-2)*SIZE;
    }while ((map[F ->y/SIZE][F -> x/SIZE] == false) || (S -> next -> x == F -> x && S -> next -> y == F -> y));

    F -> exists = true;
}

bool IsDead_() {
    if (map[S -> next-> y/SIZE][S -> next-> x/SIZE] == false) {
        Node* cur = S;
        while (cur != NULL) {
            Node* next = cur->next;
            free(cur);
            cur = next;
        }
        free(F);
        return true;
    }
    return false;
}

void DrawScore_() {
    char s[20];
    sprintf(s,"得分：%d",score);
    settextstyle(75,0,"微软雅黑");
    outtextxy(0,HEIGHT,s);
}

void DrawFood_() {
    if (F -> exists == true) {
        setfillcolor(RED);
        fillrectangle(F-> x,F -> y,F-> x + SIZE,F -> y+ SIZE);
    }

}

//渲染蛇
void DrawSnack_() {
    Node* head = S -> next;
    while (head != NULL) {

        setfillcolor(BLUE);
        fillrectangle(head -> x,head -> y,head -> x + SIZE,head -> y+ SIZE);
        head = head -> next;
    }
}