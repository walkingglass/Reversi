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
    printf("�´Ѫ��a(Player A): %c\n", Player_A);
    printf("�մѪ��a(Player B): %c\n", Player_B);
    printf("����I���C��: %d\n", Background_color);
    printf("�´��C��: %d\n", Player_A_color);
    printf("�մ��C��: %d\n", Player_B_color);
    printf("�s�۪����P�ѥ[��: %d\n", normal_point);
    printf("����u�[��: %d\n", bonus_point);
    printf("[����u-1]����: %d\n", penalty_point);
    printf("AI�H���H����: %f\n", random);
    printf("�q���U�ѳt��(����)(�V�����C�q���t��): %d\n", delar_time);
    printf("�Y�ɷƹ���m: %d\n", Mouse_movement_display);
    printf("�k��Ѥl�������ԲӸ��: %d\n", Mouse_right_display);
    printf("����AI�� ���ݭn�I���@�U�ѽL(�����ɯ�F��AI����): %d\n", AI_skip);
    printf("�����X���[��: %d\n", distance_point);
    printf("�����X���[�����v: %d\n", distance_point_variation);
}

