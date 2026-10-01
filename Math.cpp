#include "Math.h"

//声明随机数种子
std::random_device rd;
std::mt19937 gen(rd());

//获取随机数
int RandInt_(int lower,int upper) {
    if(lower > upper)
    {
        int temp = lower;
        lower = upper;
        upper = temp;
    }
    std::uniform_int_distribution<int> dis(lower, upper);
    return dis(gen);
}
