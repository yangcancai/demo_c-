//
// Created by Administrator on 2020/7/7.
//
#include "MathFunctions.h"
#include "common/IBase.h"
#include <cmath>
float my_sqrt(float v){
    IBase* p = new IBase();
    p->Init();
    delete p;
    return sqrt(v);
}
