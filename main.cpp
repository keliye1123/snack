#include <iostream>
#include <chrono>
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
        std::chrono::steady_clock::time_point start_time;
        std::chrono::steady_clock::time_point end_time;
        while (true) {
            start_time = std::chrono::steady_clock::now();
            //输入控制
            mainWorld.Input_();


            //逻辑更新
            mainWorld.Update_();

            //渲染
            BeginBatchDraw();
            cleardevice();

            mainWorld.Render_();

            EndBatchDraw();

            //帧率控制
            end_time = std::chrono::steady_clock::now();
            delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
            if (delta_time < 1000/FPS) Sleep(1000/FPS - delta_time);

        }


    }
};


int main() {
    Engine::Init_();

    Engine::Run_();
}
