#pragma once
#include "graphics.h"
#include <windows.h>
#include "Thread/poll.h"

// //玩家1的蛇头位置
// #define PLAYER1_HEAD_X    300
// #define PLAYER1_HEAD_Y    300
// #define PLAYER1_DIRECTION RIGHT  //玩家1蛇的初始方向
// extern int player1_score;        //玩家1的分数
// extern Node* player1_S;          //联机模式下玩家1的蛇节点
// extern Direction player1_dir ;   //玩家1蛇的方向
//
// //玩家2的蛇头位置
// #define PLAYER2_HEAD_X    300
// #define PLAYER2_HEAD_Y    375
// #define PLAYER2_DIRECTION RIGHT  //玩家2蛇的初始方向
// extern int player2_score;        //玩家2的分数
// extern Node* player2_S;          //连接模式下玩家2的蛇节点
// extern Direction player2_dir ;   //玩家1蛇的方向
//
// extern int cur_player;           //当前主机操作的玩家编号
// extern bool exchange_dir;        //当前主机玩家的方向是否改变

//为房间对战提前创建线程
extern ThreadPoll pool;

