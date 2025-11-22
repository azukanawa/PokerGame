#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../Library/IO.h"
#include "../Library/Init.h"
#include "../Library/Function.h"

#define FALSE 0
#define TRUE 1
#define CARDS_NUM 5    // 每个玩家手牌数
#define SPADE 4        // 黑桃
#define HEART 3        // 红心
#define CLUB 2         // 梅花
#define DIAMOND 1      // 方片
#define CARDS_TOTAL 52 // 卡牌总数

int main()
{
    srand((unsigned int)time(NULL)); // 获取随机数种子

    while (client_escape_or_not() == TRUE) // 判断用户是否要退出游戏
    {
        int players_num = num_of_players(); // 记录玩家数量

        int players_cards[players_num][CARDS_NUM]; // 存储玩家的手牌

        int players_winning_status[players_num]; // 用于记录玩家特征值判断谁胜谁负

        /*初始化*/
        players_cards_init(players_num, CARDS_NUM, players_cards); // 初始化玩家手牌区
        int cards_left[CARDS_TOTAL + 1] = {
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
            1 * 10 + DIAMOND, 2 * 10 + DIAMOND, 3 * 10 + DIAMOND, 4 * 10 + DIAMOND,
            5 * 10 + DIAMOND, 6 * 10 + DIAMOND, 7 * 10 + DIAMOND, 8 * 10 + DIAMOND,
            9 * 10 + DIAMOND, 10 * 10 + DIAMOND, 11 * 10 + DIAMOND, 12 * 10 + DIAMOND,
            13 * 10 + DIAMOND,

            0};                                                           // 存储还没发出去的牌，用一个三位数代表是什么牌，个位是花色，百位和十位是点数
        players_winning_status_init(players_winning_status, players_num); // 玩家特征值初始化

        /*游戏流程*/
        deliver_cards(cards_left, players_cards, &players_cards[players_num - 1][CARDS_NUM - 1]); // 发牌

        sort_cards(players_cards, players_num); // 按点数大小理牌

        for (int i = 0; i < players_num; i++)
        {
            printf("Player %2d:", i + 1);

            for (int j = 0; j < CARDS_NUM; j++)
            {
                printf("%d ", players_cards[i][j]);
            }
            printf("\n");
        }

        who_wins(players_cards, players_num, players_winning_status);
    }

    return 0;
}
