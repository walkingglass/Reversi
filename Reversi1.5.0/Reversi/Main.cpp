#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "Mouse.h"
#include "WindowsAPI.h"
#include "Set.h"

#include <iostream>
#include <string>
#include <cctype>
#include <cstdio>

float size = 1;//自適應大小(應為1)

void LoadFile();

Board reversi;
Set set;


int main()
{   
    uint8_t end;
    do {
        reversi.wave = 1;
        short wave_old = 0;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD bufferSize = { 120, 253 }; //設置螢幕緩衝區大小為80行，253列 {寬度, 高度}
        SetConsoleScreenBufferSize(hConsole, bufferSize);

        Mouse mouse;

        if (BOARD_SIZE > 8)size += (BOARD_SIZE - 8) * 0.1f;
        else if (BOARD_SIZE < 8)size -= (8 - BOARD_SIZE) * 0.1f;

        FontSize(12, 16);//字體大小
        FullScreen();
        ExitFullScreen();
        
        SetCursorPos(GetSystemMetrics(SM_CXSCREEN) * 0.5, GetSystemMetrics(SM_CYSCREEN) * 0.2);//移動滑鼠
        Sleep(25);

        mouse.MouseTracking("start");
        system("cls");//清除終端

        FontSize(30 / size, 40 / size);//字體大小
        FullScreen();




        reversi.CreateBoard();//創建棋盤
        reversi.JudgeBoard(reversi.wave);
        reversi.ClearOK();
        reversi.CopyBoard(reversi.wave);


        while (TRUE)
        {
            reversi.JudgeBoard(reversi.wave);
            if(wave_old!= reversi.wave)//移除翻棋才再翻棋的可能(同回合重複翻棋)
            { 
                reversi.Reversal(reversi.wave - 2);
                wave_old = reversi.wave;
            }
            if (reversi.HaveOK() == 1)
                reversi.wave++;

            reversi.ClearOK();
            reversi.JudgeBoard(reversi.wave);
            reversi.JudgeBoard(reversi.wave);//二次虛擬判別(OK用)
            reversi.AICount(reversi.wave);
            reversi.ShowBoard(reversi.wave);//顯示棋盤
            reversi.CopyBoard(reversi.wave);

            Mouse mouse;


            if (reversi.Ending(reversi.wave) == 1)
                break;


            uint8_t result = 0;
            short MouseX = 0, MouseY = 0;

            if ((reversi.wave % 2 == 1 && set.Player_A == PLAYER) || (reversi.wave % 2 == 0 && set.Player_B == PLAYER))
            {
                result = mouse.MouseTracking("main");
                MouseX = mouse.getMouseX();
                MouseY = mouse.getMouseY();
                system("cls");
            }
            if (set.Player_A == AI && set.Player_B == AI)
            {
                if (reversi.wave % 2 == 1)
                    reversi.wave += reversi.AIPut(BLACK);
                else
                    reversi.wave += reversi.AIPut(WHITE);

                
            
                if (!set.AI_skip)
                    result = mouse.MouseTracking("main");
                
                Sleep(set.delar_time);
            }
            if (result == 0 && MouseX >= 0 && MouseY >= 0 && MouseX < BOARD_SIZE && MouseY < BOARD_SIZE)//左鍵
            {
                if (reversi.wave % 2 == 1)
                {
                    if (set.Player_A == PLAYER)
                        reversi.wave += reversi.ChangeBoard(PLAYER, BLACK, MouseX, MouseY);
                    else if (set.Player_A == AI)
                        reversi.wave += reversi.AIPut(BLACK);
                }
                else
                {
                    if (set.Player_B == PLAYER)
                        reversi.wave += reversi.ChangeBoard(PLAYER, WHITE, MouseX, MouseY);
                    else if (set.Player_B == AI)
                        reversi.wave += reversi.AIPut(WHITE);

                }
            }
            else if (result == 1)//存檔
            {
                char filename[64] = "board_data.board";
                system("cls");//清除終端

                printf("\33[?25h請輸入檔案名稱：");
                scanf(" %63[a-zA-Z0-9_./-+]", filename);

                fflush(stdin);  // 清除輸入緩衝區

                reversi.SaveToFile(filename);
            }
            else if (result == 2)//提檔
            {
                LoadFile();
            }
            else if (result == 3)//設置
            {
                system("cls");
                FontSize(21, 28);//字體大小
                set.set_up();

                while (true)
                {
                  Mouse mouse_set;
                  uint8_t re = mouse_set.MouseTracking("set");
                  set.set_up();
                  if (re == 1)break;
                }
                FontSize(30 / size, 40 / size);//字體大小
                system("cls");
            }
            else if (result == 4)//右鍵(>=4)
            {
                reversi.RightButtom(reversi.wave, MouseX, MouseY);
            }
        }

        printf("\33[?25l");

        printf("\33[12;0H黑棋有:%d顆\n白棋有:%d顆\n", reversi.CountBoard(BLACK), reversi.CountBoard(WHITE));
        if (reversi.CountBoard(BLACK) > reversi.CountBoard(WHITE))
            printf("黑方獲勝\n");
        else if (reversi.CountBoard(BLACK) < reversi.CountBoard(WHITE))
            printf("白方獲勝\n");
        else
            printf("雙方平手\n");
        printf("╔");
        printf("═════");
        printf("╗");
        printf("\n║ 繼續║");
        printf("\n╚");
        printf("═════");
        printf("╝\n");
        while (true)
        {
            Mouse mouse_win;
            uint8_t result = mouse_win.MouseTracking("win");
            if (result == 1)//設置
            {
                system("cls");
                FontSize(21, 28);//字體大小
                set.set_up();

                while (true)
                {
                  Mouse mouse_set;
                  uint8_t re = mouse_set.MouseTracking("set");
                  set.set_up();
                  if (re == 1)break;
                }
                FontSize(30 / size, 40 / size);//字體大小
                system("cls");
            }
            if (result == 0)break;
        }
        if (reversi.CountBoard(BLACK) > reversi.CountBoard(WHITE))
        {
            for (short i = 0; i < BOARD_SIZE * 5; i++)
            {
                for (short j = 0; j < BOARD_SIZE*4; j++)
                    printf("\33[%d;%dH○", j, i * 2);

                Sleep(50);
            }
        }
        else if (reversi.CountBoard(BLACK) < reversi.CountBoard(WHITE))
        {
            for (short i = 0; i < BOARD_SIZE * 5; i++)
            {
                for (short j = 0; j < BOARD_SIZE *4; j++)
                    printf("\33[%d;%dH●", j, i * 2);

                Sleep(50);
            }
        }
        else
        {
            for (short i = 0; i < BOARD_SIZE*4; i++)
            {
                for (short j = 0; j < BOARD_SIZE + 5; j++)
                    printf("\33[%d;%dH˙", j, i * 2);

                Sleep(50);
            }
        }



        system("cls");//清除終端
        SetCursorPos(GetSystemMetrics(SM_CXSCREEN) * 0.5, GetSystemMetrics(SM_CYSCREEN) * 0.45);//移動滑鼠

        Mouse mouse_end;
        end = mouse_end.MouseTracking("end");
    }while (end == 1);
    exit(0);
    return 0;
}

void LoadFile()
{
    while (1)
    {
        system("cls");

        printf("\33[1;%0H╔");
        printf("═════");
        printf("╗");
        printf("\33[2;%0H║ 返回║");
        printf("\33[3;%0H");
        printf("╚");
        printf("═════");
        printf("╝");

        printf("\33[4;0H");
        reversi.LoadFromFile("boards", -1);
        Mouse mouse;
        uint8_t result = mouse.MouseTracking("load");
        // 將整數轉換為字符串
        std::string resultString = std::to_string(result);
        if (result >= 3)
        {
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
                reversi.LoadFromFile("boards", result - 3);
                system("cls");//清除終端
                break;
            }
        }
        if (result == 0)
            break;
    }

}