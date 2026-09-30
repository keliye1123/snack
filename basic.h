#pragma once
#include "graphics.h"
#include <windows.h>
#include "Thread/poll.h"

#define WIDTH  900              //窗口宽度
#define HEIGHT 750              //窗口高度
#define SIZE   75               //单个方格大小
#define ORIGIN_DIRECTION RIGHT  //蛇的初始方向
#define MAXSIZE 10              //字符串最大长度
#define FPS 60                  //游戏帧率
#define FPS_GAP 12              //每隔12帧刷新FPS显示
#define SPEED 2                 //初始速度

extern long long delta_time;      //单帧时间间隔
extern int FPS_gap;               //设置FPS的渲染间隔帧数
extern long long FPS_draw;        //用于绘制FPS的值

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

extern ExMessage msg;            //消息队列

//为房间对战提前创建线程
extern ThreadPoll pool;

extern bool map[HEIGHT/SIZE][WIDTH/SIZE];//全局地图

extern POINT pt;      //全局鼠标


bool InArea_(int x1,int y1,int x2,int y2);

//获取随机数
int RandInt_(int lower,int upper);

//初始化食物
void InitFood_();

//更新食物
void UpdateFood_();

//渲染分数
void DrawScore_();

//渲染帧率显示
void DrawFPS_();