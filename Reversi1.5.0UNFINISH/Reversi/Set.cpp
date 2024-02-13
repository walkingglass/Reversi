#include "Set.h"
#include <cstdio>

char Set::Player_A = PLAYER;//PLAYER
char Set::Player_B = AI;
uint8_t Set::Background_color = 42;
uint8_t Set::Player_A_color = 37;
uint8_t Set::Player_B_color = 37;
short Set::normal_point = 100;
short Set::bonus_point = 1000;
short Set::penalty_point = -1800;
double Set::random = 0.9;
short Set::delar_time = 0;
bool Set::Mouse_movement_display = true;//false
bool Set::Mouse_right_display = true;
bool Set::AI_skip = true;
short Set::distance_point=10;
uint8_t Set::distance_point_variation=1;

void Set::set_up() 
{
    printf("黑棋玩家(Player A): %c\n", Player_A);
    printf("白棋玩家(Player B): %c\n", Player_B);
    printf("整體背景顏色: %d\n", Background_color);
    printf("黑棋顏色: %d\n", Player_A_color);
    printf("白棋顏色: %d\n", Player_B_color);
    printf("連著的不同棋加分: %d\n", normal_point);
    printf("最邊線加分: %d\n", bonus_point);
    printf("[最邊線-1]扣分: %d\n", penalty_point);
    printf("AI人性隨機數: %f\n", random);
    printf("電腦下棋速度(延遲)(越高降低電腦負擔): %d\n", delar_time);
    printf("即時滑鼠位置: %d\n", Mouse_movement_display);
    printf("右鍵棋子的內部詳細資料: %d\n", Mouse_right_display);
    printf("輪到AI時 不需要點擊一下棋盤(關閉時能了解AI評分): %d\n", AI_skip);
    printf("中心擴散加分: %d\n", distance_point);
    printf("中心擴散加分倍率: %d\n", distance_point_variation);
}

