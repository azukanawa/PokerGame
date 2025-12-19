#pragma once
#define CARDS_NUM 5

void players_cards_init(int players_num, int CARD_NUM,
                        int** players_cards);  // 玩家手牌初始化

void players_winning_status_init(int players_winning_status[],
                                 int players_num);  // 玩家特征值初始化