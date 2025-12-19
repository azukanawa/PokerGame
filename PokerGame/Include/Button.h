#pragma once
#include <easyx.h>

extern ExMessage msg;
// 检测点(x,y)是否在矩形区域(x1,y1)(x2,y2)内
int inArea(int x, int y, int x1, int y1, int x2, int y2);

// 检测矩形区域(x1,y1)(x2,y2)内的按钮是否被按下
bool button(int x1, int y1, int x2, int y2, const char* text);
