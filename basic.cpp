#include "basic.h"
#include <random>

int speed = 10 - SPEED;
int speed_gap = speed;
int score = 0;

ExMessage msg;

long long delta_time = 0;
int FPS_gap = FPS_GAP;
long long FPS_draw = 0;

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
        score += 10 - speed;
        return;
    }
    if (F -> exists ) return;

    do {
        F -> x = RandInt_(1,WIDTH/SIZE-2)*SIZE;
        F -> y = RandInt_(1,HEIGHT/SIZE-2)*SIZE;
    }while ((map[F ->y/SIZE][F -> x/SIZE] == false) || (S -> next -> x == F -> x && S -> next -> y == F -> y));

    F -> exists = true;
}

void DrawScore_() {
    char s[20];
    sprintf(s,"得分：%d",score);
    settextstyle(75,0,"微软雅黑");
    outtextxy(0,HEIGHT,s);
}

//渲染帧率显示
void DrawFPS_() {
    char s[20];
    if (FPS_gap == FPS_GAP) {
        FPS_draw = delta_time > 0 ? (long long)(1000/delta_time) : 0;
        FPS_gap = 0;
    }else {
        FPS_gap++;
    }

    sprintf(s,"FPS：%lld",FPS_draw);
    settextstyle(38,0,"微软雅黑");
    outtextxy(90,0,s);
}