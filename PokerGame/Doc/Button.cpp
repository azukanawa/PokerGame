#include "Button.h"

#include <stdio.h>
ExMessage msg = {0};
// 检测点(x,y)是否在矩形区域(x1,y1)(x2,y2)内
int inArea(int x, int y, int x1, int y1, int x2, int y2) {
  if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
    return 1;
  else
    return 0;
}

// 检测矩形区域(x1,y1)(x2,y2)内的按钮是否被按下
bool button(int x1, int y1, int x2, int y2, const char* text) {
  // 绘制按钮
  setfillcolor(LIGHTGRAY);
  fillrectangle(x1, y1, x2, y2);
  // 绘制按钮边框
  setlinecolor(BLACK);
  rectangle(x1, y1, x2, y2);
  // 绘制按钮文本
  settextcolor(BLACK);
  settextstyle(24, 0, "微软雅黑");
  outtextxy((x1 + x2 - textwidth(text)) / 2, (y1 + y2 - textheight(text)) / 2,
            text);

  if (inArea(msg.x, msg.y, x1, y1, x2, y2)) {
    // 鼠标悬停效果
    setfillcolor(LIGHTCYAN);
    fillrectangle(x1, y1, x2, y2);
    // 绘制按钮边框
    setlinecolor(BLACK);
    rectangle(x1, y1, x2, y2);
    // 绘制按钮文本
    settextcolor(BLACK);
    settextstyle(24, 0, "微软雅黑");
    outtextxy((x1 + x2 - textwidth(text)) / 2, (y1 + y2 - textheight(text)) / 2,
              text);
  }
  // 检测按钮是否被按下
  if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x1, y1, x2, y2)) {
    return true;
  } else
    return false;
}
