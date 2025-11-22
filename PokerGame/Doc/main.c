#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../Library/IO.h"
#include "../Library/Init.h"
#include "../Library/Function.h"

#define FALSE 0
#define TRUE 1
#define CARDS_NUM 5 // 每个玩家手牌数
#define SPADE 4     // 黑桃
#define HEART 3     // 红心
#define CLUB 2      // 梅花
#define DIAMOND 1   // 方片
#define CARDS_TOTAL 52

int main()
{
    srand((unsigned int)time(NULL)); // 获取随机数种子

    while (client_escape_or_not() == TRUE) // 判断用户是否要退出游戏
    {
        int players_num = num_of_players(); // 记录玩家数量

        int players_cards[players_num][CARDS_NUM]; // 存储玩家的手牌

        /*初始化*/
        players_cards_init(players_num, CARDS_NUM, players_cards); // 初始化玩家手牌区
        int cards_left[CARDS_TOTAL + 1] = {SPADE * 100 + 1, SPADE * 100 + 2, SPADE * 100 + 3, SPADE * 100 + 4, SPADE * 100 + 5, SPADE * 100 + 6, SPADE * 100 + 7, SPADE * 100 + 8, SPADE * 100 + 9, SPADE * 100 + 10, SPADE * 100 + 11, SPADE * 100 + 12, SPADE * 100 + 13,
                                           HEART * 100 + 1, HEART * 100 + 2, HEART * 100 + 3, HEART * 100 + 4, HEART * 100 + 5, HEART * 100 + 6, HEART * 100 + 7, HEART * 100 + 8, HEART * 100 + 9, HEART * 100 + 10, HEART * 100 + 11, HEART * 100 + 12, HEART * 100 + 13,
                                           CLUB * 100 + 1, CLUB * 100 + 2, CLUB * 100 + 3, CLUB * 100 + 4, CLUB * 100 + 5, CLUB * 100 + 6, CLUB * 100 + 7, CLUB * 100 + 8, CLUB * 100 + 9, CLUB * 100 + 10, CLUB * 100 + 11, CLUB * 100 + 12, CLUB * 100 + 13,
                                           DIAMOND * 100 + 1, DIAMOND * 100 + 2, DIAMOND * 100 + 3, DIAMOND * 100 + 4, DIAMOND * 100 + 5, DIAMOND * 100 + 6, DIAMOND * 100 + 7, DIAMOND * 100 + 8, DIAMOND * 100 + 9, DIAMOND * 100 + 10, DIAMOND * 100 + 11, DIAMOND * 100 + 12, DIAMOND * 100 + 13,
                                           0}; // 存储还没发出去的牌，用一个三位数代表是什么牌，百位是花色，十位和个位是点数

        /*游戏流程*/
        deliver_cards(cards_left, players_cards, &players_cards[players_num - 1][CARDS_NUM - 1]); // 发牌

        for (int i = 0; i < players_num; i++)
        {
            printf("Player %2d:", i + 1);

            for (int j = 0; j < CARDS_NUM; j++)
            {
                printf("%d ", players_cards[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
