#define CARDS_NUM 5
#define CARDS_TOTAL 52
void players_cards_init(int players_num, int CARD_NUM, int players_cards[][CARDS_NUM])
{
    int index;  // 索引1号
    int index1; // 索引2号
    for (index = 0; index < players_num; index++)
    {
        for (index1 = 0; index1 < CARD_NUM; index1++)
        {
            players_cards[index][index1] = 0;
        }
    }
}
