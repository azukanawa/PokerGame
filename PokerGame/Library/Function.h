#define CARDS_NUM 5 // 每个玩家手牌数

int get_random(int a, int b); // 获得[a, b]之间的随机整数

void deliver_cards(int cards_left[], int player_cards[][CARDS_NUM], int *last_card_position); // 发牌函数