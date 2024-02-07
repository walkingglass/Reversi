#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "Mouse.h"
#include "WindowsAPI.h"

#include <iostream>
#include <string>
#include <cctype>

short int wave = 1;
float size = 1;//自適應大小(應為1)

void LoadFile();
Board reversi;
int main()
{
    Mouse mouse;//先宣告  不然外部EXE執行排版會噴

    if (BOARD_SIZE > 8)size += (BOARD_SIZE - 8) * 0.1f;
    else if (BOARD_SIZE < 8)size -= (8 - BOARD_SIZE) * 0.1f;

    FontSize(12, 16);//字體大小 不然外部EXE執行排版會噴
    WindowSize(120 * size, 30 * size);//視窗大小 不然外部EXE執行排版會噴


    mouse.StartMouseTracking();
    system("cls");//清除終端

    FontSize(30 / size, 40 / size);//字體大小
    FullScreen();




    reversi.CreateBoard();//創建棋盤
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
        reversi.ShowBoard(wave);//顯示棋盤
        reversi.CopyBoard(wave);

        Mouse mouse;
        uint8_t result = mouse.MouseTracking("滑鼠:", 0, 4 + BOARD_SIZE);
        short int MouseX = mouse.getMouseX();
        short int MouseY = mouse.getMouseY();

        if (reversi.Ending(wave) == 1)
            break;

        if (result == 0 && MouseX >= 0 && MouseY >= 0 && MouseX < BOARD_SIZE && MouseY < BOARD_SIZE)//左鍵
        {

            if (wave % 2 == 0)
                wave += reversi.ChangeBoard(PLAYER, WHITE, MouseX, MouseY);
            else
                wave += reversi.ChangeBoard(PLAYER, BLACK, MouseX, MouseY);
            system("cls");
        }
        else if (result == 1)//右鍵
        {
            reversi.RightButtom(wave, MouseX, MouseY);
        }
        else if (result == 2)//存檔
        {
            char filename[64] = "board_data.board";
            system("cls");//清除終端

            printf("\33[?25h請輸入檔案名稱：");
            scanf(" %[a-zA-Z0-9]s", filename);

            fflush(stdin);  // 清除輸入緩衝區

            reversi.SaveToFile(filename);
        }
        else if (result == 3)//提檔
        {
            LoadFile();
        }
        else if (result == 4)//設定
        {

        }
    }

    printf("\33[?25l");

    printf("\n黑棋有:%d顆\n白棋有:%d顆\n", reversi.CountBoard(BLACK), reversi.CountBoard(WHITE));
    if (reversi.CountBoard(BLACK) > reversi.CountBoard(WHITE))
    { 
        printf("黑方獲勝\n");
        Sleep(2500);
        for (short int i = 0; i < BOARD_SIZE * 5; i++)
        {
            for (short int j = 0; j < BOARD_SIZE + 5; j++)
                printf("\33[%d;%dH○", j, i * 2);

            Sleep(50);
        }
    }
    else if (reversi.CountBoard(BLACK) < reversi.CountBoard(WHITE))
    { 
        printf("白方獲勝\n");
        Sleep(2500);
        for (short int i = 0; i < BOARD_SIZE * 5; i++)
        {
            for (short int j = 0; j < BOARD_SIZE + 5; j++)
                printf("\33[%d;%dH●", j, i * 2);

            Sleep(50);
        }
    }
    else
    {
        printf("雙方平手\n");
        Sleep(2500);
        for (short int i = 0; i < BOARD_SIZE * 5; i++)
        {
            for (short int j = 0; j < BOARD_SIZE + 5; j++)
                printf("\33[%d;%dH˙", j, i * 2);

            Sleep(50);
        }
    }



    system("cls");//清除終端

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
        // 將整數轉換為字符串
        std::string resultString = std::to_string(result);

        // 檢查整數的每一位是否都是數字
        bool isDigit = true;
        for (char c : resultString) {
            if (!std::isdigit(c)) {
                isDigit = false;
                break;
            }
        }
        if (isDigit)// 整數是數字
        {
            reversi.LoadFromFile("boards", result);
            break;
        }

    }

}