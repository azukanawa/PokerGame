#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")

#include "Button.h"
#include "Function.h"
#include "Game.h"
#include "Init.h"
#include "Music.h"
#include "common.h"

int main() {
  srand((unsigned int)time(NULL) ^ (unsigned int)clock());
  // 设置绿色背景
  initgraph(800, 540);
  setbkcolor(RGB(126, 227, 71));
  cleardevice();
  setbkmode(TRANSPARENT);

  // 背景音乐
  playBackgroundMusic("music/欢乐斗地主.mp3", true, 100);

  // 主菜单背景图片
  IMAGE img_MM;
  loadimage(&img_MM, "picture\\MM.jpg", 800, 540);
  putimage(0, 0, &img_MM);

  int gamestart = 0;  // 游戏开始标志

  int players_num = 0;  // 记录玩家数量

  while (1)  // 主菜单循环
  {
    peekmessage(&msg, EX_MOUSE, true);

    BeginBatchDraw();
    setlinestyle(PS_SOLID, 3);
    // 开始、退出游戏按钮
    if (gamestart == 0 && button(300, 200, 500, 250, "三人游戏")) {
      printf("Game Start 3\n");
      gamestart = 1;
      players_num = 3;
    }
    if (gamestart == 0 && button(300, 270, 500, 320, "四人游戏")) {
      printf("Game Start 4\n");
      gamestart = 1;
      players_num = 4;
    }
    if (gamestart == 0 && button(300, 340, 500, 390, "五人游戏")) {
      printf("Game Start 5\n");
      gamestart = 1;
      players_num = 5;
    }
    if (gamestart == 0 && button(300, 410, 500, 460, "退出游戏")) {
      closegraph();
      break;
    }
    EndBatchDraw();

    int* money = (int*)malloc(players_num * sizeof(int));  // 存储每个玩家的钱数

    for (int a = 0; a < players_num; a++) {
      money[a] = 2000;
    }

    while (gamestart == 1)  // 特定人数循环
    {
      cleardevice();
      // int players_cards[players_num][CARDS_NUM]; // 存储玩家的手牌
      int** players_cards = (int**)malloc(players_num * sizeof(int*));
      for (int i = 0; i < players_num; i++) {
        players_cards[i] = (int*)malloc(CARDS_NUM * sizeof(int));
      }
      if (players_cards == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
      }

      // int players_winning_status[players_num]; //
      // 用于记录玩家特征值判断谁胜谁负
      int* players_winning_status = (int*)malloc(players_num * sizeof(int));

      int cards_left[CARDS_TOTAL] = {
          // 黑桃
          1 * 10 + SPADE, 2 * 10 + SPADE, 3 * 10 + SPADE, 4 * 10 + SPADE,
          5 * 10 + SPADE, 6 * 10 + SPADE, 7 * 10 + SPADE, 8 * 10 + SPADE,
          9 * 10 + SPADE, 10 * 10 + SPADE, 11 * 10 + SPADE, 12 * 10 + SPADE,
          13 * 10 + SPADE,

          // 红桃
          1 * 10 + HEART, 2 * 10 + HEART, 3 * 10 + HEART, 4 * 10 + HEART,
          5 * 10 + HEART, 6 * 10 + HEART, 7 * 10 + HEART, 8 * 10 + HEART,
          9 * 10 + HEART, 10 * 10 + HEART, 11 * 10 + HEART, 12 * 10 + HEART,
          13 * 10 + HEART,

          // 梅花
          1 * 10 + CLUB, 2 * 10 + CLUB, 3 * 10 + CLUB, 4 * 10 + CLUB,
          5 * 10 + CLUB, 6 * 10 + CLUB, 7 * 10 + CLUB, 8 * 10 + CLUB,
          9 * 10 + CLUB, 10 * 10 + CLUB, 11 * 10 + CLUB, 12 * 10 + CLUB,
          13 * 10 + CLUB,

          // 方块
          1 * 10 + DIAMOND, 2 * 10 + DIAMOND, 3 * 10 + DIAMOND,
          4 * 10 + DIAMOND, 5 * 10 + DIAMOND, 6 * 10 + DIAMOND,
          7 * 10 + DIAMOND, 8 * 10 + DIAMOND, 9 * 10 + DIAMOND,
          10 * 10 + DIAMOND, 11 * 10 + DIAMOND, 12 * 10 + DIAMOND,
          13 * 10 +
              DIAMOND};  // 存储还没发出去的牌，用一个三位数代表是什么牌，个位是花色，百位和十位是点数

      players_winning_status_init(players_winning_status,
                                  players_num);  // 玩家特征值初始化

      int* state = (int*)malloc(
          players_num *
          sizeof(
              int));  // 玩家下注倍数（state[0]为真人下注倍数，剩余为电脑下注倍数）

      /*游戏流程*/

      deliver_cards(cards_left, players_cards, players_num);  // 发牌

      sort_cards(players_cards, players_num);  // 按点数大小理牌

      int i = 0;
      printf("Player%2d:", i + 1);
      double win_probability = 0;
      double* pwin_probability = &win_probability;
      estimate_win_probability(players_cards[i], players_num, pwin_probability);
      printf("胜率预测：%lf\n", *pwin_probability);

      int winner = who_wins(players_cards, players_num,
                            players_winning_status);  // 找到谁赢了
      int loser_val = 0;
      int* loser = &loser_val;  // 输光的玩家编号指针传出

      printf("Player%2d wins!\n", winner);  // 找到谁赢了

      switch (players_num) {
        case 3:
          game_3p(players_cards, players_num, state, money, winner, &gamestart,
                  loser, pwin_probability);  // 三人游戏界面
          break;
        case 4:
          game_4p(players_cards, players_num, state, money, winner, &gamestart,
                  loser, pwin_probability);  // 四人游戏界面
          break;
        case 5:
          game_5p(players_cards, players_num, state, money, winner, &gamestart,
                  loser, pwin_probability);  // 五人游戏界面
          break;
        default:
          break;
      }

      Sleep(3000);
      if (gamestart == 0) {
        end_game(loser);  // 结束游戏界面
      } else if (gamestart == 1) {
        winner_display(winner);  // 胜利界面
      }

      flushmessage();  // 清空消息队列

      while (gamestart == 0) {
        peekmessage(&msg, EX_KEY, true);
        if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
          cleardevice();  // 回到主菜单前清屏
          loadimage(&img_MM, "picture\\MM.jpg", 800, 540);
          putimage(0, 0, &img_MM);
          break;
        }
      }

      while (gamestart == 1)  // 等待回车开始新游戏
      {
        peekmessage(&msg, EX_KEY, true);
        if (msg.message == WM_KEYDOWN && msg.vkcode == VK_RETURN) {
          break;
        }
        if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
          gamestart = 0;
          cleardevice();  // 回到主菜单前清屏
          loadimage(&img_MM, "picture\\MM.jpg", 800, 540);
          putimage(0, 0, &img_MM);
          break;
        }
      }

      // 释放内存
      if (players_cards != NULL) {
        for (int i = 0; i < players_num; i++) {
          free(players_cards[i]);
        }
        free(players_cards);
        players_cards = NULL;
      }
      free(players_winning_status);
      free(state);
    }
    gamestart = 0;
    msg.message = 0;
    free(money);
  }

  return 0;
}
