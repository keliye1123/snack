# 贪吃蛇联机版     
该游戏是基于easyx图形库的经典贪贪吃蛇游戏，既有经典单机模式，也包含1v1的联机对战模式。
## 项目代码介绍  
- basic.cpp/basic.h:宏定义了地图的长宽、每个方格大大小和单机模式下蛇的初始方向和位置等，声明了一些常用的全局变量、结构体
函数，也声明了联机模式玩家1和玩家2的全局变量。
- FileManager.h:用于本地排行榜简单的文件写入与读取操作。
- together.h:联机模式下蛇的更新计算和渲染的实现。
- World.cpp/World.h:游戏的渲染场景是由basis中的cur_level决定的，World.cpp/World.h决定场景更新。
- Client：游戏windows客户端用于通信的函数封装。
- Server：游戏服务端代码，要在Linux或者WSL环境下才能运行
- Thread:封装线程管理类。
- bin:可执行文件路径。

