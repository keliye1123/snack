#pragma once
#include "graphics.h"
#include <windows.h>
#include "Thread/poll.h"

#define WIDTH  900              //窗口宽度
#define HEIGHT 750              //窗口高度
#define SIZE   75               //单个方格大小
#define HEAD_POSITION_X  300    //蛇头初始x位置
#define HEAD_POSITION_Y  300    //蛇头初始y位置
#define ORIGIN_DIRECTION RIGHT  //蛇的初始方向
#define MAXSIZE 10              //字符串最大长度
#define  MAX_PLAYERS 5          //排行榜最大人数

extern int before_level;  //之前场景
extern int cur_level;  //当前场景
extern bool exchange_level_flag;
extern int speed;                  //速度
extern int score;                  //分数
extern int len1;                   //围城模式的排行榜人数
extern int len2;                   //无限模式的排行榜人数

//蛇节点定义
typedef struct snack {
    int x;
    int y;
    struct snack *next;
}Node;

extern Node* S;     //单人模式下的蛇节点

//方向类型枚举
enum Direction {
    LEFT,//0
    UP,//1
    RIGHT,//2
    DOWN//3
};

//玩家1的蛇头位置
#define PLAYER1_HEAD_X    300
#define PLAYER1_HEAD_Y    300
#define PLAYER1_DIRECTION RIGHT  //玩家1蛇的初始方向
extern int player1_score;        //玩家1的分数
extern Node* player1_S;          //联机模式下玩家1的蛇节点
extern Direction player1_dir ;   //玩家1蛇的方向

//玩家2的蛇头位置
#define PLAYER2_HEAD_X    300
#define PLAYER2_HEAD_Y    375
#define PLAYER2_DIRECTION RIGHT  //玩家2蛇的初始方向
extern int player2_score;        //玩家2的分数
extern Node* player2_S;          //连接模式下玩家2的蛇节点
extern Direction player2_dir ;   //玩家1蛇的方向

extern int cur_player;           //当前主机操作的玩家编号
extern bool exchange_dir;        //当前主机玩家的方向是否改变

typedef struct people {
    char name[MAXSIZE] = {};//MAXSIZE = 10
    int  score = 0;
}players;

//为房间对战提前创建线程
extern ThreadPoll pool;

extern players players1[MAX_PLAYERS];
extern players players2[MAX_PLAYERS];

extern bool map[HEIGHT/SIZE][WIDTH/SIZE];//全局地图

extern Direction dir ;//蛇的方向
extern POINT pt;      //全局鼠标

//食物
typedef struct food {
    int x;
    int y;
    bool exists;
} Food;

extern Food* F;

bool InArea_(int x1,int y1,int x2,int y2);

//获取随机数
int RandInt_(int lower,int upper);

//排序
void BubbleSort(players players_[],int len);

//初始化蛇
void InitSnack_();

//初始化食物
void InitFood_();

//更新食物
void UpdateFood_();

//判断是否死亡
bool IsDead_();

//渲染分数
void DrawScore_();

//渲染食物
void DrawFood_();

//渲染蛇
void DrawSnack_();