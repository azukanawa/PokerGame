#include <stdio.h>
#include <stdlib.h>

#include "common.h"

int get_random(int a, int b)  // 获得[a, b]的随机整数
{
  if (a > b) {  // 处理参数无效的情况
    printf("Invalid random range: a=%d, b=%d\n", a, b);
    return a;  // 或返回默认值，避免崩溃
  }
  return rand() % (b - a + 1) + a;
}

void deliver_cards(int cards_left[], int** player_cards,  // 发牌函数
                   int players_num) {
  int total_need_cards = players_num * CARDS_NUM;
  int card_left = CARDS_TOTAL;

  // 初始化玩家手牌为无效值
  for (int i = 0; i < players_num; i++) {
    for (int j = 0; j < CARDS_NUM; j++) {
      player_cards[i][j] = 0;
    }
  }

  // 确保有足够的牌可发（根据num_of_players的校验，这里理论上恒成立）
  if (total_need_cards > CARDS_TOTAL) {
    printf("Error: Not enough cards!\n");
    return;
  }

  for (int i = 0; i < players_num; i++) {  // 按玩家发牌
    for (int j = 0; j < CARDS_NUM; j++) {  // 每个玩家发5张
      int position = get_random(0, card_left - 1);
      player_cards[i][j] =
          cards_left[position];  // 直接给当前玩家的当前位置发牌

      // 移除已发的牌（将最后一张牌移到当前位置，减少剩余牌数量）
      cards_left[position] = cards_left[card_left - 1];
      card_left--;
    }
  }
}

void sort_cards(int** player_cards, int players_num)  // 理牌函数
{
  int index = 0;   // 一号索引
  int index1 = 0;  // 二号索引
  int index2 = 0;  // 三号索引
  int cpy = 0;     // 短暂记录复制下来的数据

  for (index = 0; index < players_num; index++)  // 依次为每个玩家理牌
  {
    /*冒泡排序*/
    for (index1 = 0; index1 < CARDS_NUM - 1; index1++) {
      for (index2 = 0; index2 < CARDS_NUM - 1 - index1; index2++) {
        if (player_cards[index][index2] > player_cards[index][index2 + 1]) {
          cpy = player_cards[index][index2];
          player_cards[index][index2] = player_cards[index][index2 + 1];
          player_cards[index][index2 + 1] = cpy;
        }
      }
    }
  }
}

int who_wins(int** player_cards, int player_num,  // 判断输赢并找到赢家
             int players_winning_status[]) {
  int index = 0;   // 索引一号
  int index1 = 0;  // 索引二号

  // int suits[player_num][CARDS_NUM];  // 花色数组
  int** suits = (int**)malloc(player_num * sizeof(int*));
  if (suits == NULL) {
    printf("Memory allocation failed!\n");
    return -1;
  }
  for (int i = 0; i < player_num; i++) {
    suits[i] = (int*)malloc(CARDS_NUM * sizeof(int));
    if (suits[i] == NULL) {
      printf("Memory allocation failed!\n");
      return -1;
    }
  }

  // int points[player_num][CARDS_NUM]; // 点数数组
  int** points = (int**)malloc(player_num * sizeof(int*));
  if (points == NULL) {
    printf("Memory allocation failed!\n");
    return -1;
  }
  for (int i = 0; i < player_num; i++) {
    points[i] = (int*)malloc(CARDS_NUM * sizeof(int));
    if (points[i] == NULL) {
      printf("Memory allocation failed!\n");
      return -1;
    }
  }

  for (index = 0; index < player_num; index++)  // 分别记录花色和点数
  {
    for (index1 = 0; index1 < CARDS_NUM; index1++) {
      suits[index][index1] =
          player_cards[index][index1] % 10;  // 花色取个位上的数
      points[index][index1] =
          player_cards[index][index1] / 10;  // 点数取百位和十位的数
    }
  }

  sort_cards(suits, player_num);  // 用理牌函数从小到大整理一下花色

  for (index = 0; index < player_num; index++) {
    /*判断是否是顺子*/
    if (points[index][CARDS_NUM - 1] - points[index][0] == 4 &&
        points[index][0] != points[index][1] &&
        points[index][1] != points[index][2] &&
        points[index][2] != points[index][3] &&
        points[index][3] != points[index][4]) {
      /*判断是否同花*/
      if (suits[index][CARDS_NUM - 1] == suits[index][0]) {
        /*是就是同花顺*/
        /*用一个四位数来表示玩家特征，最高位是牌型，往下两位是核心牌的点数，个位是最大关键牌的花色*/
        players_winning_status[index] =
            FLUSH * 1000 + player_cards[index][CARDS_NUM - 1];
        continue;
      } else {
        /*否则就是顺子*/
        players_winning_status[index] =
            STRAIGHT * 1000 + player_cards[index][CARDS_NUM - 1];
        continue;
      }
    }

    /*判断是否是炸弹*/
    else if (points[index][0] == points[index][3]) {
      players_winning_status[index] = FOUR * 1000 + player_cards[index][3];
      continue;
    } else if (points[index][1] == points[index][4]) {
      players_winning_status[index] = FOUR * 1000 + player_cards[index][4];
      continue;
    }

    /*判断是否是三带二*/
    else if (points[index][0] == points[index][2] &&
             points[index][3] == points[index][4]) {
      players_winning_status[index] =
          FULL_HOUSE * 1000 + player_cards[index][2];
      continue;
    } else if (points[index][2] == points[index][4] &&
               points[index][0] == points[index][1]) {
      players_winning_status[index] =
          FULL_HOUSE * 1000 + player_cards[index][4];
      continue;
    }

    /*判断是否是三张*/
    else if (points[index][0] == points[index][2]) {
      players_winning_status[index] = THREE * 1000 + player_cards[index][2];
      continue;
    } else if (points[index][2] == points[index][4]) {
      players_winning_status[index] = THREE * 1000 + player_cards[index][4];
      continue;
    } else if (points[index][1] == points[index][3]) {
      players_winning_status[index] = THREE * 1000 + player_cards[index][3];
      continue;
    }

    /*判断是否是两对*/
    else if (points[index][0] == points[index][1] &&
             points[index][2] == points[index][3]) {
      players_winning_status[index] = TWO_PAIRS * 1000 + player_cards[index][3];
      continue;
    } else if (points[index][0] == points[index][1] &&
               points[index][3] == points[index][4]) {
      players_winning_status[index] = TWO_PAIRS * 1000 + player_cards[index][4];
      continue;
    } else if (points[index][1] == points[index][2] &&
               points[index][3] == points[index][4]) {
      players_winning_status[index] = TWO_PAIRS * 1000 + player_cards[index][4];
      continue;
    }

    /*判断是否是对子*/
    else if (points[index][0] == points[index][1]) {
      players_winning_status[index] = PAIR * 1000 + player_cards[index][1];
      continue;
    } else if (points[index][1] == points[index][2]) {
      players_winning_status[index] = PAIR * 1000 + player_cards[index][2];
      continue;
    } else if (points[index][2] == points[index][3]) {
      players_winning_status[index] = PAIR * 1000 + player_cards[index][3];
      continue;
    } else if (points[index][3] == points[index][4]) {
      players_winning_status[index] = PAIR * 1000 + player_cards[index][4];
      continue;
    }

    else {
      players_winning_status[index] =
          NONE * 1000 + player_cards[index][CARDS_NUM - 1];
      continue;
    }
  }
  for (int i = 0; i < player_num; i++) {
    free(suits[i]);
    free(points[i]);
  }
  free(suits);
  free(points);

  int max = 0;         // 记录最大的特征值
  int max_player = 0;  // 记录有最大特征值的玩家是哪位

  for (max = players_winning_status[0], max_player = 0, index = 0;
       index < player_num; index++)  // 遍历数组找到最大的状态值以及对应的玩家
  {
    if (players_winning_status[index] > max) {
      max = players_winning_status[index];
      max_player = index;
    }
  }

  return max_player + 1;  // 由于从0开始遍历，所以返回值加一
}

double estimate_win_probability(int my_cards[], int player_num,  // 估算胜率函数
                                double* pwin_probability) {
  int point = 1;
  int suit = 1;
  int found = 0;
  int cards[CARDS_TOTAL - CARDS_NUM];
  int cards_cpy[CARDS_TOTAL - CARDS_NUM];
  int j = 0;
  int i = 0;
  int card_left = CARDS_TOTAL - CARDS_NUM;
  int* player_winning_status = (int*)malloc(player_num * sizeof(int));
  int win = 0;
  int index = 0;

  for (suit = 1; suit <= 4; suit++)  // 记录除了被测胜率者手牌以外的牌
  {
    for (point = 1; point <= 13; point++) {
      for (i = 0; i < CARDS_NUM; i++) {
        if (point * 10 + suit == my_cards[i]) {
          found = 1;
          break;
        }
      }
      if (found == 1) {
        found = 0;
        continue;
      }
      cards[j] = point * 10 + suit;
      cards_cpy[j] = point * 10 + suit;
      j++;
    }
  }

  int** players =
      (int**)malloc(player_num * sizeof(int*));  // 放置模拟状态下玩家手牌
  for (i = 0; i < player_num; i++) {
    players[i] = (int*)malloc(CARDS_NUM * sizeof(int));
  }

  for (i = 0; i < CARDS_NUM; i++) {
    players[0][i] = my_cards[i];
  }

  for (index = 0; index < SIMULATION_GAMES; index++) {
    for (i = 1; i < player_num; i++) {   // 按玩家发牌
      for (j = 0; j < CARDS_NUM; j++) {  // 每个玩家发5张
        int position = get_random(0, card_left - 1);
        players[i][j] = cards[position];  // 直接给当前玩家的当前位置发牌

        // 移除已发的牌（将最后一张牌移到当前位置，减少剩余牌数量）
        cards[position] = cards[card_left - 1];
        card_left--;
      }
    }
    sort_cards(players, player_num);
    int winner =
        who_wins(players, player_num, player_winning_status);  // 找到胜者
    if (winner == 1) {
      win++;  // 计算胜场
    }
    for (i = 0; i < CARDS_TOTAL - CARDS_NUM; i++) {
      cards[i] = cards_cpy[i];  // 复位牌堆
    }
    card_left = CARDS_TOTAL - CARDS_NUM;
  }

  free(player_winning_status);
  for (i = 0; i < player_num; i++) {
    free(players[i]);
  }
  free(players);
  *pwin_probability = 1.0 * win / SIMULATION_GAMES;
  return 1.0 * win / SIMULATION_GAMES;
}

int bet(int num, int* state, int* money, int winner, int* loser,  // 下注函数
        int** player_card, double* pwin_probability) {
  int i;
  int final_money = 0;  // 所有玩家的钱加起来
  for (i = 1; i < num; i++) {
    estimate_win_probability(player_card[i], num, pwin_probability);
    double win_probability = *pwin_probability;
    printf("玩家%d胜率为：%lf\n", i + 1, win_probability);
    if (win_probability >= 0.5) {
      state[i] = 2;
    } else {
      state[i] = 1;
    }
  }

  for (int i = 0; i < num; i++) {
    if (i != winner - 1) {
      money[i] -= state[winner - 1] * 250 * state[i];
      final_money += state[winner - 1] * 250 * state[i];
    }
  }
  money[winner - 1] += final_money;

  for (i = 0; i < num; i++) {
    if (money[i] <= 0) {
      *loser = i + 1;
      return 0;
    }
  }

  return 1;
}
