#include "Set.h"
#include <cstdio>

char Set::Player_A = PLAYER;//PLAYER
char Set::Player_B = AI;
uint8_t Set::Background_color = 42;
uint8_t Set::Player_A_color = 37;
uint8_t Set::Player_B_color = 37;
uint8_t Set::hint_chess_color = 37;
uint8_t Set::empty_chess_color = 37;
short Set::normal_point = 100;
short Set::bonus_point = 1000;
short Set::penalty_point = -1800;
short Set::distance_point = 10;
short Set::distance_point_variation = 1;
double Set::random = 0.9;
short Set::delar_time = 0;
bool Set::Mouse_movement_display = true;//false
bool Set::Mouse_right_display = true;
bool Set::AI_skip = true;
bool Set::hint_chess_open = true;


void Set::set_up()
{
    printf("\33[1;0H╔");
    printf("═════");
    printf("╗");
    printf("\33[2;0H║ 返回║");
    printf("\33[3;0H");
    printf("╚");
    printf("═════");
    printf("╝\n");

    printf("\33[1;10H╔");
    printf("═════════");
    printf("╗");
    printf("\33[2;10H║ 離開遊戲║");
    printf("\33[3;10H");
    printf("╚");
    printf("═════════");
    printf("╝\n");

    /*printf("\33[1;23H╔");
    printf("═══════════");
    printf("╗");
    printf("\33[2;23H║ AI數值調適║");
    printf("\33[3;23H");
    printf("╚");
    printf("═══════════");
    printf("╝\n");*/

    printf("黑棋玩家(Player A):  ");
    (Player_A == PLAYER) ? printf("\33[34mPLAYER\33[0m  AI\n") : printf("PLAYER  \33[34mAI\33[0m\n");

    printf("白棋玩家(Player B):  ");
    (Player_B == PLAYER) ? printf("\33[34mPLAYER\33[0m  AI\n") : printf("PLAYER  \33[34mAI\33[0m\n");

    printf("整體背景顏色:[\33[%dm  \33[0m]  \33[5m點擊設置\33[0m->[", Background_color);
    for (uint8_t i = 40; i < 48; i++)
        printf("\33[%dm  ",i);
    printf("\33[0m]\n");

    printf("黑棋顏色     [\33[%dm\33[%dm○\33[0m]  \33[5m點擊設置\33[0m->[", Background_color, Player_A_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm○", i);
    printf("\33[0m]\n");

    printf("白棋顏色:    [\33[%dm\33[%dm●\33[0m]  \33[5m點擊設置\33[0m->[", Background_color, Player_B_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm●", i);
    printf("\33[0m]\n");

    printf("提示棋顏色:  [\33[%dm\33[%dm˙\33[0m]  \33[5m點擊設置\33[0m->[", Background_color, hint_chess_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm˙", i);
    printf("\33[0m]\n");

    printf("空棋顏色:    [\33[%dm\33[%dm□\33[0m]  \33[5m點擊設置\33[0m->[", Background_color, empty_chess_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm□", i);
    printf("\33[0m]\n");

    printf("連著的不同棋加分:%7d\33[35mpoint\33[0m\n", normal_point);
    printf("最邊線加分:      %7d\33[35mpoint\33[0m\n", bonus_point);
    printf("[最邊線-1]扣分:  %7d\33[35mpoint\33[0m\n", penalty_point);
    printf("中心擴散加分:    %7d\33[35mpoint\33[0m\n", distance_point);
    printf("中心擴散加分倍率:%7d\33[35m倍\33[0m\n", distance_point_variation);

    printf("電腦下棋速度:    %7d\33[35mms\33[0m\n", delar_time);

    printf("AI人性隨機數:    %7.2f(%.2f\33[35m%%\33[0m)\n", random, random*100);
    
    printf("即時滑鼠位置:            ");
    (Mouse_movement_display == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");
    
    printf("右鍵棋子的內部詳細資料:  ");
    (Mouse_right_display == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");

    printf("輪到AI時關閉點擊:        ");
    (AI_skip == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");

    printf("提示棋:                  ");
    (hint_chess_open == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");
}

