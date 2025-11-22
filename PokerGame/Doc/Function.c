#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define CARDS_NUM 5    // 每个玩家手牌数
#define CARDS_TOTAL 52 // 总牌数
#define SPADE 4        // 黑桃
#define HEART 3        // 红心
#define CLUB 2         // 梅花
#define DIAMOND 1      // 方片

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
        int position = get_random(0, card_left - 1); // 发第几张牌

        *location_now = cards_left[position]; // 存储在玩家手牌中

        location_now++; // 往后移动一位准备发牌

        card_left--; // 剩余牌数减一

        while (cards_left[position] != 0) // 将发出去的牌拿掉
        {
            cards_left[position] = cards_left[position + 1];

            position++;
        }
    }
}
