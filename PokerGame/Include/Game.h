#pragma once
void game_3p(int** players_cards, int players_num, int state[], int money[],
             int winner, int* gamestart, int* loser,
             double* pwin_probability);  // 三人游戏界面
void game_4p(int** players_cards, int players_num, int state[], int money[],
             int winner, int* gamestart, int* loser,
             double* pwin_probability);  // 四人游戏界面
void game_5p(int** players_cards, int players_num, int state[], int money[],
             int winner, int* gamestart, int* loser,
             double* pwin_probability);  // 五人游戏界面
void winner_display(int winner);         // 胜利界面
void end_game(int* loser);               // 结束游戏界面