#include <conio.h>
#include <easyx.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Button.h"
#include "Function.h"
void game_3p(int** players_cards, int players_num, int state[], int money[],
             int winner, int* gamestart, int* loser,
             double* pwin_probability)  // 三人游戏界面
{
  cleardevice();
  setlinecolor(WHITE);
  setlinestyle(PS_SOLID, 4);
  line(0, 180, 800, 180);  // 分割线1
  line(0, 360, 800, 360);  // 分割线2

  IMAGE img_pokerbk;
  loadimage(&img_pokerbk, "picture\\poker_bk.jpg", 100, 140);
  for (int i = 30; i <= 390; i += 180) {
    for (int j = 80; j <= 680; j += 150) {
      putimage(j, i, &img_pokerbk);  // 牌背图片
    }
  }

  settextcolor(BLACK);
  settextstyle(28, 0, "微软雅黑");
  setaspectratio(1.0f, 1.0f);
  setbkmode(TRANSPARENT);
  char str[20] = "玩家1";
  char str_money[50] = "2000元";
  for (int i = 1; i <= 3; i++) {
    sprintf_s(str, "玩家%d", i);
    sprintf_s(str_money, "%d元", money[i - 1]);
    outtextxy(3, 3 + (i - 1) * 180, str);
    outtextxy(3, 33 + (i - 1) * 180, str_money);
  }

  for (int i = 30, a = 0; i <= 390; i += 180, a++) {
    for (int j = 80, b = 0; j <= 680; j += 150, b++) {
      Sleep(640);
      IMAGE img_poker;
      char str_poker[50] = "picture\\poker_";
      sprintf_s(str_poker, "picture\\poker_%d.jpg", players_cards[a][b]);
      loadimage(&img_poker, str_poker, 100, 140);
      putimage(j, i, &img_poker);
      if (a == 0 && b == 4) {
        int bet_done = 0;  // 玩家下注完成标志
        int paintX2 = 1;   // 是否绘制X2按钮标志
        int paint_tip = 1;
        while (!bet_done) {
          peekmessage(&msg, EX_MOUSE | EX_KEY | EX_CHAR | EX_WINDOW, true);
          BeginBatchDraw();
          if (button(5, 75, 60, 105, "X1")) {
            clearrectangle(3, 72, 63, 148);
            settextstyle(28, 0, "微软雅黑");
            outtextxy(5, 80, "倍数：");
            outtextxy(10, 105, "X1");
            state[0] = 1;
            bet_done = 1;
            paintX2 = 0;
          }
          if (paintX2) {
            if (button(5, 115, 60, 145, "X2")) {
              clearrectangle(3, 72, 63, 148);
              settextstyle(28, 0, "微软雅黑");
              outtextxy(5, 80, "倍数：");
              outtextxy(10, 105, "X2");
              state[0] = 2;
              bet_done = 1;
            }
          }
          if (paint_tip) {
            if (button(70, 2, 110, 26, "提示")) {
              clearrectangle(68, 0, 112, 27);
              settextstyle(17, 0, "微软雅黑");
              char string[100] = {0};
              sprintf_s(string, "胜率:%.2lf%%", *pwin_probability * 100);
              outtextxy(75, 5, string);
              paint_tip = 0;
            }
          }
          EndBatchDraw();
        }
        if (bet(players_num, state, money, winner, loser, players_cards,
                pwin_probability) == 0) {
          *gamestart = 0;
        }
        // 显示其他玩家的下注倍数
        for (int i = 2; i <= 3; i++) {
          char str_bet[10];
          sprintf_s(str_bet, "X%d", state[i - 1]);
          settextstyle(28, 0, "微软雅黑");
          outtextxy(5, 80 + (i - 1) * 180, "倍数：");
          outtextxy(10, 105 + (i - 1) * 180, str_bet);
        }
      }
    }
  }
}
void game_4p(int** players_cards, int players_num, int state[], int money[],
             int winner, int* gamestart, int* loser,
             double* pwin_probability)  // 四人游戏界面
{
  cleardevice();
  setlinecolor(WHITE);
  setlinestyle(PS_SOLID, 3);
  line(0, 135, 800, 135);  // 分割线1
  line(0, 270, 800, 270);  // 分割线2
  line(0, 405, 800, 405);  // 分割线3
  IMAGE img_pokerbk;
  loadimage(&img_pokerbk, "picture\\poker_bk.jpg", 80, 110);
  for (int i = 17; i <= 510; i += 135) {
    for (int j = 100; j <= 680; j += 145) {
      putimage(j, i, &img_pokerbk);  // 牌背图片
    }
  }

  settextcolor(BLACK);
  settextstyle(30, 0, "微软雅黑");
  setaspectratio(1.0f, 1.0f);
  setbkmode(TRANSPARENT);
  char str[20] = "玩家1";
  char str_money[50] = "2000元";
  for (int i = 1; i <= 4; i++) {
    sprintf_s(str, "玩家%d", i);
    sprintf_s(str_money, "%d元", money[i - 1]);
    outtextxy(3, 3 + (i - 1) * 135, str);
    outtextxy(3, 31 + (i - 1) * 135, str_money);
  }

  for (int i = 17, a = 0; i <= 510; i += 135, a++) {
    for (int j = 100, b = 0; j <= 680; j += 145, b++) {
      Sleep(640);
      IMAGE img_poker;
      char str_poker[50] = "picture\\poker_";
      sprintf_s(str_poker, "picture\\poker_%d.jpg", players_cards[a][b]);
      loadimage(&img_poker, str_poker, 80, 110);
      putimage(j, i, &img_poker);
      if (a == 0 && b == 4) {
        int bet_done = 0;  // 玩家下注完成标志
        int paintX2 = 1;   // 是否绘制X2按钮标志
        int paint_tip = 1;
        while (!bet_done) {
          peekmessage(&msg, EX_MOUSE | EX_KEY | EX_CHAR | EX_WINDOW, true);
          BeginBatchDraw();
          if (button(5, 60, 60, 90, "X1")) {
            clearrectangle(3, 57, 63, 133);
            settextstyle(26, 0, "微软雅黑");
            outtextxy(5, 65, "倍数：");
            outtextxy(10, 90, "X1");
            state[0] = 1;
            bet_done = 1;
            paintX2 = 0;
          }
          if (paintX2) {
            if (button(5, 100, 60, 130, "X2")) {
              clearrectangle(3, 57, 63, 133);
              settextstyle(26, 0, "微软雅黑");
              outtextxy(5, 65, "倍数：");
              outtextxy(10, 90, "X2");
              state[0] = 2;
              bet_done = 1;
            }
          }
          if (paint_tip) {
            if (button(50, 2, 90, 26, "提示")) {
              clearrectangle(49, 0, 91, 27);
              settextstyle(17, 0, "微软雅黑");
              char string[100] = {0};
              sprintf_s(string, "胜率:%.2lf%%", *pwin_probability * 100);
              outtextxy(50, 2, string);
              paint_tip = 0;
            }
          }
          EndBatchDraw();
        }
        if (bet(players_num, state, money, winner, loser, players_cards,
                pwin_probability) == 0) {
          *gamestart = 0;
        }
        // 显示其他玩家的下注倍数
        for (int i = 2; i <= 4; i++) {
          char str_bet[10];
          sprintf_s(str_bet, "X%d", state[i - 1]);
          settextstyle(26, 0, "微软雅黑");
          outtextxy(5, 65 + (i - 1) * 135, "倍数：");
          outtextxy(10, 90 + (i - 1) * 135, str_bet);
        }
      }
    }
  }
}

void game_5p(int** players_cards, int players_num, int state[], int money[],
             int winner, int* gamestart, int* loser,
             double* pwin_probability)  // 五人游戏界面
{
  cleardevice();
  setlinecolor(WHITE);
  setlinestyle(PS_SOLID, 2);
  line(0, 108, 800, 108);  // 分割线1
  line(0, 216, 800, 216);  // 分割线2
  line(0, 324, 800, 324);  // 分割线3
  line(0, 432, 800, 432);  // 分割线4
  IMAGE img_pokerbk;
  loadimage(&img_pokerbk, "picture\\poker_bk.jpg", 70, 95);
  for (int i = 8; i <= 536; i += 108) {
    for (int j = 100; j <= 660; j += 140) {
      putimage(j, i, &img_pokerbk);  // 牌背图片
    }
  }
  settextcolor(BLACK);
  settextstyle(20, 0, "微软雅黑");
  setaspectratio(1.0f, 1.0f);
  setbkmode(TRANSPARENT);
  char str[20] = "玩家1";
  char str_money[50] = "2000元";
  for (int i = 1; i <= 5; i++) {
    sprintf_s(str, "玩家%d", i);
    sprintf_s(str_money, "%d元", money[i - 1]);
    outtextxy(3, 3 + (i - 1) * 108, str);
    outtextxy(3, 25 + (i - 1) * 108, str_money);
  }
  for (int i = 8, a = 0; i <= 536; i += 108, a++) {
    for (int j = 100, b = 0; j <= 660; j += 140, b++) {
      Sleep(640);
      IMAGE img_poker;
      char str_poker[50] = "picture\\poker_";
      sprintf_s(str_poker, "picture\\poker_%d.jpg", players_cards[a][b]);
      loadimage(&img_poker, str_poker, 70, 95);
      putimage(j, i, &img_poker);
      if (a == 0 && b == 4) {
        int bet_done = 0;  // 玩家下注完成标志
        int paintX2 = 1;   // 是否绘制X2按钮标志
        int paint_tip = 1;
        while (!bet_done) {
          peekmessage(&msg, EX_MOUSE | EX_KEY | EX_CHAR | EX_WINDOW, true);
          BeginBatchDraw();
          if (button(3, 50, 60, 70, "X1")) {
            clearrectangle(1, 47, 63, 103);
            settextstyle(23, 0, "微软雅黑");
            outtextxy(7, 55, "倍数：");
            outtextxy(13, 80, "X1");
            state[0] = 1;
            bet_done = 1;
            paintX2 = 0;
          }
          if (paintX2) {
            if (button(3, 80, 60, 100, "X2")) {
              clearrectangle(1, 47, 63, 103);
              settextstyle(23, 0, "微软雅黑");
              outtextxy(8, 55, "倍数：");
              outtextxy(13, 80, "X2");
              state[0] = 2;
              bet_done = 1;
            }
          }
          if (paint_tip) {
            if (button(50, 2, 90, 26, "提示")) {
              clearrectangle(49, 0, 91, 27);
              settextstyle(17, 0, "微软雅黑");
              outtextxy(50, 2, "胜率：");
              char string[100] = {0};
              sprintf_s(string, "%.2lf%%", *pwin_probability * 100);
              outtextxy(50, 19, string);
              paint_tip = 0;
            }
          }
          EndBatchDraw();
        }

        if (bet(players_num, state, money, winner, loser, players_cards,
                pwin_probability) == 0) {
          *gamestart = 0;
        }
        // 显示其他玩家的下注倍数
        // 显示其他玩家的下注倍数
        for (int i = 2; i <= 5; i++) {
          char str_bet[10];
          sprintf_s(str_bet, "X%d", state[i - 1]);
          settextstyle(23, 0, "微软雅黑");
          outtextxy(7, 55 + (i - 1) * 108, "倍数：");
          outtextxy(13, 80 + (i - 1) * 108, str_bet);
        }
      }
    }
  }
}

void winner_display(int winner)  // 胜利界面
{
  // 胜利消息框
  setlinecolor(LIGHTGRAY);
  setlinestyle(PS_SOLID, 9);
  setfillcolor(BLACK);
  fillrectangle(280, 190, 520, 350);  // 填充的矩形

  // 胜利文本
  settextcolor(WHITE);
  settextstyle(45, 0, "微软雅黑");
  setaspectratio(1.0f, 1.0f);
  setbkmode(TRANSPARENT);
  char str[20] = "玩家1获胜！";
  sprintf_s(str, "玩家%d获胜！", winner);
  outtextxy(290 + (240 - textwidth(str)) / 2, 200 + (80 - textheight(str)) / 2,
            str);

  // 继续消息
  settextstyle(30, 0, "微软雅黑");
  char str1[30] = "按回车再来一局";
  char str2[] = "按ESC回到主菜单";
  outtextxy(280 + (240 - textwidth(str1)) / 2,
            260 + (80 - textheight(str1)) / 2, str1);
  outtextxy(280 + (240 - textwidth(str2)) / 2,
            235 + (80 - textheight(str2)) / 2, str2);
}
void end_game(int* loser) {
  // 结束消息框
  setlinecolor(LIGHTGRAY);
  setlinestyle(PS_SOLID, 9);
  setfillcolor(BLACK);
  fillrectangle(280, 190, 520, 350);  // 填充的矩形

  // 胜利文本
  settextcolor(WHITE);
  settextstyle(45, 0, "微软雅黑");
  setaspectratio(1.0f, 1.0f);
  setbkmode(TRANSPARENT);
  char str[20] = "玩家1输光了";
  sprintf_s(str, "玩家%d输光了", *loser);
  outtextxy(290 + (240 - textwidth(str)) / 2, 200 + (80 - textheight(str)) / 2,
            str);

  // 继续消息
  settextstyle(30, 0, "微软雅黑");
  char str1[30] = "游戏结束";
  char str2[] = "按ESC回到主菜单";
  outtextxy(280 + (240 - textwidth(str1)) / 2,
            260 + (80 - textheight(str1)) / 2, str1);
  outtextxy(280 + (240 - textwidth(str2)) / 2,
            235 + (80 - textheight(str2)) / 2, str2);
}