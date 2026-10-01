//
// Created by 25738 on 2026/9/30.
//

#include "Food.h"
#include "../Macro.h"
#include "../Math.h"
#include "../World.h"

Food::Food() {
    this -> x = 0;
    this -> y = 0;
    this -> exists = false;
}

void Food::SetExists_(const bool& flag) {
    this -> exists = flag;
}

bool Food::GetExists_() const {
    return this -> exists;
}

//食物初始化
void Food::InitFood_() {
    do {
        this -> x = RandInt_(1,WIDTH/SIZE-2)*SIZE;
        this -> y = RandInt_(1,HEIGHT/SIZE-2)*SIZE;
    }while (mainWorld.map[this ->y/SIZE][this -> x/SIZE] == false);

    this -> exists = true;
}

void Food::UpdateFood_() {
    if (mainWorld.LocalSnack -> GetHead() -> next -> x == this -> x && mainWorld.LocalSnack -> GetHead() -> next -> y == this -> y) {
        this -> exists = false;
        mainWorld.LocalSnack -> SetScore_(mainWorld.LocalSnack -> GetScore_() + 10 - mainWorld.LocalSnack -> GetSpeed_());
        return;
    }
    if (this -> exists ) return;

    do {
        this -> x = RandInt_(1,WIDTH/SIZE-2)*SIZE;
        this -> y = RandInt_(1,HEIGHT/SIZE-2)*SIZE;
    }while ((mainWorld.map[this ->y/SIZE][this -> x/SIZE] == false) || (mainWorld.LocalSnack -> GetHead() -> next -> x == this -> x && mainWorld.LocalSnack -> GetHead() -> next -> y == this -> y));

    this -> exists = true;
}

void Food::DrawFood_() const{
    if (this -> exists == true) {
        setfillcolor(RED);
        fillrectangle(this -> x,this -> y,this -> x + SIZE,this -> y+ SIZE);
    }

}