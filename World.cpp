#include "World.h"

#include "Level/Map1.h"
#include "Level/Map2.h"
#include "Level/Map3.h"
#include "Level/Menu.h"
#include "Level/End.h"
#include "Level/Set.h"
#include "Level/Rank.h"
#include "Level/Waiting.h"

World mainWorld;

void World::Input_() {
    switch (cur_level) {
        case 0:
            MenuInput_();
            break;

        case 1:
            InPutMap1_();
            break;

        case 2:
            InitEnd_();
            InputEnd_();
            break;

        case 3:
            InPutMap2_();
            break;

        case 4:
            SetInput_();
            break;

        case 5:
            InputRank_();
            break;

        case 6:
            InputMap3_();
            break;

        case 7:
            InputWaiting_();
            break;

        default:break;
    }

}

void World::Update_() {
    switch (cur_level) {
        case 0:
            break;

        case 1:
            InitMap1_();
            UpdateMap1_();
            break;

        case 2:
            break;

        case 3:
            InitMap2_();
            UpdateMap2_();
            break;

        case 6:
            InitMap3_();
            UpdateMap3_();
            break;

        case 7:
            InitWaiting_();
            break;

        default:
            break;
    }
}

void World::Render_() {
    switch (cur_level) {
        case 0:
            MenuRender_();
            break;

        case 1:
            RenderMap1_();
            break;

        case 2:
            RenderEnd_();
            break;

        case 3:
            RenderMap2_();
            break;

        case 4:
            SetRRender_();
            break;

        case 5:
            RenderRank_();
            break;

        case 6:
            RenderMap3_();
            break;

        case 7:
            RenderWaiting_();

        default:
            break;
    }
}
