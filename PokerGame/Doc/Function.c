#include <stdlib.h>
#include <stdio.h>
#define FALSE 0
#define TRUE 1
#define CARDS_NUM 5          // 每个玩家手牌数
#define CARDS_TOTAL 52       // 总牌数
#define SPADE 4              // 黑桃
#define HEART 3              // 红心
#define CLUB 2               // 梅花
#define DIAMOND 1            // 方片
#define FLUSH 7              // 同花顺
#define STRAIGHT 6           // 顺子
#define FOUR 5               // 炸弹
#define FULL_HOUSE 4         // 三带二
#define THREE 3              // 三张
#define TWO_PAIRS 2          // 两对
#define PAIR 1               // 对子
#define NONE 0               // 野牌
int get_random(int a, int b) // 获得[a, b]的随机整数
{
    return rand() % (b - a + 1) + a;
}

void deliver_cards(int cards_left[], int player_cards[][CARDS_NUM], int *last_card_position) // 发牌函数
{
    int *location_now = &player_cards[0][0]; // 记录把牌发到哪里

    int card_left = CARDS_TOTAL; // 记录剩余牌数，便于随机位置

    while (location_now <= last_card_position)
    {
        int position = get_random(0, card_left - 1); // 随机判断发第几张牌

        *location_now = cards_left[position]; // 将该位置的牌存储在玩家手牌中

        location_now++; // 准备给下一个位置发牌

        card_left--; // 剩余牌数减一

        while (cards_left[position] != 0) // 将发出去的牌拿掉
        {
            cards_left[position] = cards_left[position + 1];

            position++;
        }
    }
}

void sort_cards(int player_cards[][CARDS_NUM], int players_num) // 理牌函数
{
    int index = 0;  // 一号索引
    int index1 = 0; // 二号索引
    int index2 = 0; // 三号索引
    int cpy = 0;    // 短暂记录复制下来的数据

    for (index = 0; index < players_num; index++) // 依次为每个玩家理牌
    {
        /*冒泡排序*/
        for (index1 = 0; index1 < CARDS_NUM - 1; index1++)
        {
            for (index2 = 0; index2 < CARDS_NUM - 1 - index1; index2++)
            {
                if (player_cards[index][index2] > player_cards[index][index2 + 1])
                {
                    cpy = player_cards[index][index2];
                    player_cards[index][index2] = player_cards[index][index2 + 1];
                    player_cards[index][index2 + 1] = cpy;
                }
            }
        }
    }
}

int who_wins(int player_cards[][CARDS_NUM], int player_num, int players_winning_status[])
{
    int index = 0; // 索引一号
    int index1 = 0;
    int suits[player_num][CARDS_NUM];  // 花色数组
    int points[player_num][CARDS_NUM]; // 点数数组

    for (index = 0; index < player_num; index++) // 分别记录花色和点数
    {
        for (index1 = 0; index1 < CARDS_NUM; index1++)
        {
            suits[index][index1] = player_cards[index][index1] % 10;  // 花色取个位上的数
            points[index][index1] = player_cards[index][index1] / 10; // 点数取百位和十位的数
        }
    }

    sort_cards(suits, player_num); // 用理牌函数从小到大整理一下花色

    for (index = 0; index < player_num; index++)
    {

        /*判断是否是顺子*/
        if (points[index][CARDS_NUM - 1] - points[index][0] == 4 && points[index][0] != points[index][1] && points[index][1] != points[index][2] && points[index][2] != points[index][3] && points[index][3] != points[index][4])
        {
            /*判断是否同花*/
            if (suits[index][CARDS_NUM - 1] == suits[index][0])
            {
                /*是就是同花顺*/
                /*用一个四位数来表示玩家特征，千位是牌型，百位和十位是最大的点数，个位是最大牌的花色*/
                players_winning_status[index] = FLUSH * 1000 + points[index][CARDS_NUM - 1] * 10 + player_cards[index][CARDS_NUM - 1] % 10;
                continue;
            }
            else
            {
                /*否则就是顺子*/
                players_winning_status[index] = STRAIGHT * 1000 + points[index][CARDS_NUM - 1] * 10 + player_cards[index][CARDS_NUM - 1] % 10;
                continue;
            }
        }

        /*判断是否是炸弹*/
        else if (points[index][0] == points[index][3] || points[index][1] == points[index][4])
        {
            players_winning_status[index] = FOUR * 1000 + points[index][CARDS_NUM - 1] * 10 + player_cards[index][CARDS_NUM - 1] % 10;
            continue;
        }

        /*判断是否是三带二*/
        else if (points[index][0] == points[index][2] && points[index][3] == points[index][4] || points[index][2] == points[index][4] && points[index][0] == points[index][1])
        {
            players_winning_status[index] = FULL_HOUSE * 1000 + points[index][CARDS_NUM - 1] * 10 + player_cards[index][CARDS_NUM - 1] % 10;
            continue;
        }

        /*判断是否是三张*/
        else if (points[index][0] == points[index][2] || points[index][2] == points[index][4] || points[index][1] == points[index][3])
        {
            players_winning_status[index] = THREE * 1000 + points[index][CARDS_NUM - 1] * 10 + player_cards[index][CARDS_NUM - 1] % 10;
            continue;
        }

        /*判断是否是两对*/
        else if (points[index][0] == points[index][1] && points[index][2] == points[index][3] || points[index][0] == points[index][1] && points[index][3] == points[index][4] || points[index][1] == points[index][2] && points[index][3] == points[index][4])
        {
            players_winning_status[index] = TWO_PAIRS * 1000 + points[index][CARDS_NUM - 1] * 10 + player_cards[index][CARDS_NUM - 1] % 10;
            continue;
        }

        /*判断是否是对子*/
        else if (points[index][0] == points[index][1] || points[index][1] == points[index][2] || points[index][2] == points[index][3] || points[index][3] == points[index][4])
        {
            players_winning_status[index] = PAIR * 1000 + points[index][CARDS_NUM - 1] * 10 + player_cards[index][CARDS_NUM - 1] % 10;
            continue;
        }

        else
        {
            players_winning_status[index] = NONE * 1000 + points[index][CARDS_NUM - 1] * 10 + player_cards[index][CARDS_NUM - 1] % 10;
            continue;
        }
    }

    for (int i = 0; i < player_num; i++)
    {
        printf("Player %2d:", i + 1);

        for (int j = 0; j < CARDS_NUM; j++)
        {
            printf("%d ", suits[i][j]);
        }

        printf("\n");
    }
    for (int i = 0; i < player_num; i++)
    {
        printf("Player %2d:", i + 1);

        for (int j = 0; j < CARDS_NUM; j++)
        {
            printf("%d ", points[i][j]);
        }

        printf("\n");
    }
    for (int i = 0; i < player_num; i++)
    {
        printf("%d ", players_winning_status[i]);
    }
}