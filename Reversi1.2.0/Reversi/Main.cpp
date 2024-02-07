#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "Mouse.h"
#include "WindowsAPI.h"

#include <iostream>
#include <string>
#include <cctype>


float size = 1;//�۾A���j�p(����1)
char PLAYER_A = PLAYER;//��
char PLAYER_B = AI;//��

void LoadFile();
    Board reversi;

int main()
{
    reversi.wave = 1;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { 120, 253 }; //�]�m�ù��w�İϤj�p��80��A253�C {�e��, ����}
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    Mouse mouse;//���ŧi  ���M�~��EXE����ƪ��|�Q

    if (BOARD_SIZE > 8)size += (BOARD_SIZE - 8) * 0.1f;
    else if (BOARD_SIZE < 8)size -= (8 - BOARD_SIZE) * 0.1f;
    
    FontSize(12, 16);//�r��j�p ���M�~��EXE����ƪ��|�Q
    WindowSize(120 * size, 30 * size);//�����j�p ���M�~��EXE����ƪ��|�Q


    mouse.StartMouseTracking();
    system("cls");//�M���׺�

    FontSize(30 / size, 40 / size);//�r��j�p
    FullScreen();




    reversi.CreateBoard();//�ЫشѽL
    reversi.JudgeBoard(reversi.wave);
    reversi.ClearOK();
    reversi.CopyBoard(reversi.wave);


    while (TRUE)
    {
        reversi.JudgeBoard(reversi.wave);
        reversi.Reversal(reversi.wave - 2);
        if (reversi.HaveOK() == 1)
            reversi.wave++;

        reversi.ClearOK();
        reversi.JudgeBoard(reversi.wave);
        reversi.JudgeBoard(reversi.wave);//�G�������P�O(OK��)
        reversi.AICount(reversi.wave);
        reversi.ShowBoard(reversi.wave);//��ܴѽL
        reversi.CopyBoard(reversi.wave);

        Mouse mouse;
        uint8_t result = mouse.MouseTracking("�ƹ�:", 0, 4 + BOARD_SIZE);
        short int MouseX = mouse.getMouseX();
        short int MouseY = mouse.getMouseY();

        if (reversi.Ending(reversi.wave) == 1)
            break;

        if (result == 0 && MouseX >= 0 && MouseY >= 0 && MouseX < BOARD_SIZE && MouseY < BOARD_SIZE)//����
        {
            if (reversi.wave % 2 == 1)
            { 
                if (PLAYER_A == PLAYER)
                    reversi.wave += reversi.ChangeBoard(PLAYER, BLACK, MouseX, MouseY);
                else if (PLAYER_A == AI)
                    reversi.wave += reversi.AIPut(BLACK);
            }
            else
            { 
                if (PLAYER_B == PLAYER)
                    reversi.wave += reversi.ChangeBoard(PLAYER, WHITE, MouseX, MouseY);
                else if (PLAYER_B == AI)
                    reversi.wave += reversi.AIPut(WHITE);

            }
            system("cls");
        }
        else if (result == 1)//�k��
        {
            reversi.RightButtom(reversi.wave, MouseX, MouseY);
        }
        else if (result == 2)//�s��
        {
            char filename[64] = "board_data.board";
            system("cls");//�M���׺�

            printf("\33[?25h�п�J�ɮצW�١G");
            scanf(" %63[a-zA-Z0-9_./-+]", filename);

            fflush(stdin);  // �M����J�w�İ�

            reversi.SaveToFile(filename);
        }
        else if (result == 3)//����
        {
            LoadFile();
        }
        else if (result == 4)//�]�w
        {

        }
    }

    printf("\33[?25l");

    printf("\n�´Ѧ�:%d��\n�մѦ�:%d��\n", reversi.CountBoard(BLACK), reversi.CountBoard(WHITE));
    if (reversi.CountBoard(BLACK) > reversi.CountBoard(WHITE))
    { 
        printf("�¤����\n");
        Sleep(2500);
        for (short int i = 0; i < BOARD_SIZE * 5; i++)
        {
            for (short int j = 0; j < BOARD_SIZE + 5; j++)
                printf("\33[%d;%dH��", j, i * 2);

            Sleep(50);
        }
    }
    else if (reversi.CountBoard(BLACK) < reversi.CountBoard(WHITE))
    { 
        printf("�դ����\n");
        Sleep(2500);
        for (short int i = 0; i < BOARD_SIZE * 5; i++)
        {
            for (short int j = 0; j < BOARD_SIZE + 5; j++)
                printf("\33[%d;%dH��", j, i * 2);

            Sleep(50);
        }
    }
    else
    {
        printf("���襭��\n");
        Sleep(2500);
        for (short int i = 0; i < BOARD_SIZE * 5; i++)
        {
            for (short int j = 0; j < BOARD_SIZE + 5; j++)
                printf("\33[%d;%dH��", j, i * 2);

            Sleep(50);
        }
    }



    system("cls");//�M���׺�

    Mouse mouse_end;
    mouse_end.EndMouseTracking();
    exit;
    return 0;
}

void LoadFile()
{
    while (1)
    {
        system("cls");

        printf("\33[1;%0H��");
        printf("����������");
        printf("��");
        printf("\33[2;%0H�� ���}��");
        printf("\33[3;%0H");
        printf("��");
        printf("����������");
        printf("��");

        printf("\33[4;0H");
        reversi.LoadFromFile("boards", -1);
        Mouse mouse;
        uint8_t result = mouse.LoadMouseTracking();
        // �N����ഫ���r�Ŧ�
        std::string resultString = std::to_string(result);
        if (result >= 3)
        {
            // �ˬd��ƪ��C�@��O�_���O�Ʀr
            bool isDigit = true;
            for (char c : resultString) {
                if (!std::isdigit(c)) {
                    isDigit = false;
                    break;
                }
            }
            if (isDigit)// ��ƬO�Ʀr
            {
                reversi.LoadFromFile("boards", result - 3);
                system("cls");//�M���׺�
                break;
            }
        }
        if (result == 0)
            break;
    }

}