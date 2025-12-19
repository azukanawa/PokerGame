#include "common.h"

void players_cards_init(int players_num, int CARD_NUM,
                        int** players_cards)  // 玩家手牌初始化
{
  int index = 0;   // 索引1号
  int index1 = 0;  // 索引2号
  for (index = 0; index < players_num; index++) {
    for (index1 = 0; index1 < CARD_NUM; index1++) {
      players_cards[index][index1] = 0;
    }
  }
}

void players_winning_status_init(int players_winning_status[],
                                 int players_num)  // 玩家特征值初始化
{
  int index = 0;  // 索引1号
  for (index = 0; index < players_num; index++) {
    players_winning_status[index] = 0;
  }
}