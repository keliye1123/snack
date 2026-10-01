#pragma once
#include"../World.h"

inline void InitMap2_() {
    for (int i = 0;i <= HEIGHT/SIZE-1;i++ ) {
        for (int j = 0;j <= WIDTH/SIZE-1;j++ ) {
            mainWorld.map[i][j] = true;
        }
    }

    mainWorld.LocalSnack -> InitSnack_();
    mainWorld.LocalFood -> InitFood_();
    mainWorld.leaderBoard -> SetLevelFlag("Map2");
}

inline void InPutMap2_() {
    mainWorld.LocalSnack ->ControlSnack_();
}

inline void UpdateMap2_() {
    if (mainWorld.LocalSnack -> GetGap_() == mainWorld.LocalSnack -> GetSpeed_()) {
        mainWorld.LocalSnack -> SetGap_(0);
        //逻辑更新
        mainWorld.LocalSnack -> UpdateSnack2_();
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

//渲染背景2
inline void DrawBackground2_() {

    setlinecolor(WHITE);
    setlinestyle(PS_SOLID,2);
    for (int i = 0;i*SIZE <= WIDTH;i++ ) {

        line(i*SIZE,0,i*SIZE,750);
    }
    for (int j = 0;j*SIZE <= HEIGHT;j++) {
        line(0,j*SIZE,900,j*SIZE);
    }
}

inline void RenderMap2_() {
    DrawBackground2_();
    mainWorld.LocalSnack -> DrawSnack_();
    mainWorld.LocalFood -> DrawFood_();
    mainWorld.LocalSnack -> DrawScore_();
}