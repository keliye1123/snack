//
// Created by 25738 on 2026/9/30.
//

#include "Food.h"

void Food::DrawFood_() {
    if (this -> exists == true) {
        setfillcolor(RED);
        fillrectangle(this -> x,this -> y,this -> x + SIZE,this -> y+ SIZE);
    }

}