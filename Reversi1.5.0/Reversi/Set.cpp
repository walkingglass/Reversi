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
    printf("\33[1;0H��");
    printf("����������");
    printf("��");
    printf("\33[2;0H�� ��^��");
    printf("\33[3;0H");
    printf("��");
    printf("����������");
    printf("��\n");

    printf("\33[1;10H��");
    printf("������������������");
    printf("��");
    printf("\33[2;10H�� ���}�C����");
    printf("\33[3;10H");
    printf("��");
    printf("������������������");
    printf("��\n");

    /*printf("\33[1;23H��");
    printf("����������������������");
    printf("��");
    printf("\33[2;23H�� AI�ƭȽվA��");
    printf("\33[3;23H");
    printf("��");
    printf("����������������������");
    printf("��\n");*/

    printf("�´Ѫ��a(Player A):  ");
    (Player_A == PLAYER) ? printf("\33[34mPLAYER\33[0m  AI\n") : printf("PLAYER  \33[34mAI\33[0m\n");

    printf("�մѪ��a(Player B):  ");
    (Player_B == PLAYER) ? printf("\33[34mPLAYER\33[0m  AI\n") : printf("PLAYER  \33[34mAI\33[0m\n");

    printf("����I���C��:[\33[%dm  \33[0m]  \33[5m�I���]�m\33[0m->[", Background_color);
    for (uint8_t i = 40; i < 48; i++)
        printf("\33[%dm  ",i);
    printf("\33[0m]\n");

    printf("�´��C��     [\33[%dm\33[%dm��\33[0m]  \33[5m�I���]�m\33[0m->[", Background_color, Player_A_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm��", i);
    printf("\33[0m]\n");

    printf("�մ��C��:    [\33[%dm\33[%dm��\33[0m]  \33[5m�I���]�m\33[0m->[", Background_color, Player_B_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm��", i);
    printf("\33[0m]\n");

    printf("���ܴ��C��:  [\33[%dm\33[%dm��\33[0m]  \33[5m�I���]�m\33[0m->[", Background_color, hint_chess_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm��", i);
    printf("\33[0m]\n");

    printf("�Ŵ��C��:    [\33[%dm\33[%dm��\33[0m]  \33[5m�I���]�m\33[0m->[", Background_color, empty_chess_color);
    for (uint8_t i = 30; i < 38; i++)
        printf("\33[%dm��", i);
    printf("\33[0m]\n");

    printf("�s�۪����P�ѥ[��:%7d\33[35mpoint\33[0m\n", normal_point);
    printf("����u�[��:      %7d\33[35mpoint\33[0m\n", bonus_point);
    printf("[����u-1]����:  %7d\33[35mpoint\33[0m\n", penalty_point);
    printf("�����X���[��:    %7d\33[35mpoint\33[0m\n", distance_point);
    printf("�����X���[�����v:%7d\33[35m��\33[0m\n", distance_point_variation);

    printf("�q���U�ѳt��:    %7d\33[35mms\33[0m\n", delar_time);

    printf("AI�H���H����:    %7.2f(%.2f\33[35m%%\33[0m)\n", random, random*100);
    
    printf("�Y�ɷƹ���m:            ");
    (Mouse_movement_display == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");
    
    printf("�k��Ѥl�������ԲӸ��:  ");
    (Mouse_right_display == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");

    printf("����AI�������I��:        ");
    (AI_skip == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");

    printf("���ܴ�:                  ");
    (hint_chess_open == true) ? printf("\33[34mTRUE\33[0m  FALSE\n") : printf("TRUE  \33[34mFALSE\33[0m\n");
}

