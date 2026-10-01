#pragma once
#include"../basic.h"
#include"../World.h"

inline void InitMap1_() {
        for (int i = 0;i <= HEIGHT/SIZE-1;i++ ) {
            for (int j = 0;j <= WIDTH/SIZE-1;j++ ) {
                mainWorld.map[i][j] = true;
            }
        }
        for (int j = 0;j <= WIDTH/SIZE-1;j++ ) {
            mainWorld.map[0][j] = false;
            mainWorld.map[HEIGHT/SIZE-1][j] = false;
        }
        for (int j = 0;j <= HEIGHT/SIZE-1;j++ ) {
            mainWorld.map[j][0] = false;
            mainWorld.map[j][WIDTH/SIZE-1] = false;
        }
        mainWorld.LocalSnack -> InitSnack_();
        mainWorld.LocalFood -> InitFood_();
        mainWorld.leaderBoard -> SetLevelFlag("Map1");

}

inline void InPutMap1_() {
    mainWorld.LocalSnack ->ControlSnack_();
}

inline void UpdateMap1_() {
    if (mainWorld.LocalSnack -> GetGap_() == mainWorld.LocalSnack -> GetSpeed_()) {
        mainWorld.LocalSnack -> SetGap_(0);
        //逻辑更新
        mainWorld.LocalSnack -> UpdateSnack_();
        mainWorld.LocalFood -> UpdateFood_();
        if (mainWorld.LocalSnack -> IsDead_()) {
            mainWorld.levelManager -> SetChangeLevel("End");
            mainWorld.levelManager -> SetFlag_(true);
            return;
        }
    }else {
        mainWorld.LocalSnack -> SetGap_(mainWorld.LocalSnack -> GetGap_() + 1);
    }
}

inline void DrawBackground1_() {
    setfillcolor(BLACK);
    fillrectangle(0,0,SIZE,HEIGHT);
    fillrectangle(0,0,WIDTH,SIZE);
    fillrectangle(0,HEIGHT - SIZE,WIDTH,HEIGHT);
    fillrectangle(WIDTH - SIZE,0,WIDTH,HEIGHT);

    setlinecolor(WHITE);
    setlinestyle(PS_SOLID,2);
    for (int i = 0;i*SIZE <= WIDTH;i++ ) {

        line(i*SIZE,0,i*SIZE,750);
    }
    for (int j = 0;j*SIZE <= HEIGHT;j++) {
        line(0,j*SIZE,900,j*SIZE);
    }
}

inline void RenderMap1_() {
    //渲染
    DrawBackground1_();
    mainWorld.LocalSnack -> DrawSnack_();
    mainWorld.LocalFood -> DrawFood_();
    mainWorld.LocalSnack -> DrawScore_();
}




