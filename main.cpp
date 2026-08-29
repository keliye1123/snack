#include <iostream>
#include "basic.h"
#include "World.h"
#include "FileManager.h"

class World;

class Engine {
    friend class World;

    //方法
public:
    static void Init_() {
        ReadFile_();
        initgraph(WIDTH,HEIGHT + SIZE);
        setbkcolor(RGB(200,200,200));
        cleardevice();
    }

    static void Run_() {
        while (true) {

            //输入控制
            mainWorld.Input_();


            //逻辑更新
            mainWorld.Update_();

            //渲染
            BeginBatchDraw();
            cleardevice();

            mainWorld.Render_();

            EndBatchDraw();

            Sleep(100);
        }


    }
};


int main() {
    Engine::Init_();

    Engine::Run_();
}
