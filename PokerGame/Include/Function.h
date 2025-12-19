#pragma once
#define CARDS_NUM 5  // 每个玩家手牌数

int get_random(int a, int b);  // 获得[a, b]的随机数

void deliver_cards(int cards_left[], int** player_cards,
                   int players_num);  // 发牌函数

void sort_cards(int** player_cards, int players_num);  // 理牌函数

int who_wins(int** player_cards, int player_num,
             int players_winning_status[]);  // 判断输赢并找到赢家

int bet(int num, int* state, int* money, int winner, int* loser,
        int** player_card, double* probability);  // 下注函数

double estimate_win_probability(int my_cards[], int player_num,
                                double* pwin_probability);  // 估算胜率函数