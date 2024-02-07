#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "Mouse.h"
#include "WindowsAPI.h"

#include <iostream>
#include <string>
#include <cctype>

short int wave = 1;
float size = 1;//�۾A���j�p(����1)

void LoadFile();
Board reversi;
int main()
{
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
    reversi.JudgeBoard(wave);
    reversi.ClearOK();
    reversi.CopyBoard(wave);


    while (TRUE)
    {
        reversi.JudgeBoard(wave);
        reversi.Reversal(wave - 2);
        if (reversi.HaveOK() == 1)
            wave++;


        reversi.ClearOK();
        reversi.JudgeBoard(wave);
        reversi.ShowBoard(wave);//��ܴѽL
        reversi.CopyBoard(wave);

        Mouse mouse;
        uint8_t result = mouse.MouseTracking("�ƹ�:", 0, 4 + BOARD_SIZE);
        short int MouseX = mouse.getMouseX();
        short int MouseY = mouse.getMouseY();

        if (reversi.Ending(wave) == 1)
            break;

        if (result == 0 && MouseX >= 0 && MouseY >= 0 && MouseX < BOARD_SIZE && MouseY < BOARD_SIZE)//����
        {

            if (wave % 2 == 0)
                wave += reversi.ChangeBoard(PLAYER, WHITE, MouseX, MouseY);
            else
                wave += reversi.ChangeBoard(PLAYER, BLACK, MouseX, MouseY);
            system("cls");
        }
        else if (result == 1)//�k��
        {
            reversi.RightButtom(wave, MouseX, MouseY);
        }
        else if (result == 2)//�s��
        {
            char filename[64] = "board_data.board";
            system("cls");//�M���׺�

            printf("\33[?25h�п�J�ɮצW�١G");
            scanf(" %[a-zA-Z0-9]s", filename);

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
        reversi.LoadFromFile("boards", -1);
        Mouse mouse;
        uint8_t result = mouse.LoadMouseTracking();
        // �N����ഫ���r�Ŧ�
        std::string resultString = std::to_string(result);

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
            reversi.LoadFromFile("boards", result);
            break;
        }

    }

}