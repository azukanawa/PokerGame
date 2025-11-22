#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define CARDS_NUM 5 // 每个玩家手牌数
#define CARDS_TOTAL 52

int client_escape_or_not(void) // 用户是否继续游戏
{
    int client_input_number; // 用户输入数字
    int client_status;       // 用户是要退出状态还是要继续状态

    printf("Press 1 to start a new game, press 0 to escape.\n"); // 按1开始游戏，按0退出游戏

    scanf("%d", &client_input_number); // 用户输入

    switch (client_input_number) // 判断用户输入数字，若输入1用户状态变量为真，若为0则用户状态变量为假
    {
    case FALSE:
        client_status = FALSE;
        break;
    case TRUE:
        client_status = TRUE;
        break;
    default:
        return client_escape_or_not(); // 返回用户状态
    }
    return client_status;
}

int num_of_players(void) // 用户输入有几名玩家
{
    float players_num; // 记录玩家数量

    printf("Please input the number of players.\n");

    scanf("%f", &players_num);

    if (players_num <= 0 || players_num - (int)players_num != 0 || players_num > (int)(CARDS_TOTAL / CARDS_NUM)) // 确保用户输入合法
    {
        return num_of_players();
    }

    return (int)players_num;
}
