#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "Mouse.h"
#include "WindowsAPI.h"
#include "Set.h"

#include <direct.h>
#include <io.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdio>

float size = 1;//自適應大小(應為1)

void LoadFile();
void setpage();

Board reversi;

Mouse mouse;
short copy_Number_of_executions, white_win = 0, black_win = 0, draw = 0,all_win=0;

int main()
{
    Set set;
    uint8_t end;

    reversi.wave = 1;
    short wave_old = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { 120, 253 }; //設置螢幕緩衝區大小為80行，253列 {寬度, 高度}
    SetConsoleScreenBufferSize(hConsole, bufferSize);


    if (BOARD_SIZE > 8)size += (BOARD_SIZE - 8) * 0.1f;
    else if (BOARD_SIZE < 8)size -= (8 - BOARD_SIZE) * 0.1f;

    FontSize(12, 16);//字體大小
    FullScreen();
    ExitFullScreen();

    SetCursorPos(GetSystemMetrics(SM_CXSCREEN) * 0.5, GetSystemMetrics(SM_CYSCREEN) * 0.2);//移動滑鼠
    Sleep(25);

    uint8_t game = mouse.MouseTracking("start");
    system("cls");//清除終端

    FontSize(30 / size, 40 / size);//字體大小
    FullScreen();


    set.LoadSetFile("boards", "Jerry.board_set");
    if (set.Player_A == AI && set.Player_B == AI)
    { 
        set.Player_A = PLAYER;
        char filename[64] = "Jerry";
        set.SaveSetFile(filename);
    }
    reversi.CreateBoard();//創建棋盤
    reversi.JudgeBoard(reversi.wave);
    reversi.ClearOK();
    reversi.CopyBoard(reversi.wave);


    while (game)
    {
        reversi.JudgeBoard(reversi.wave);
        if (wave_old != reversi.wave)//移除翻棋才再翻棋的可能(同回合重複翻棋)
        {
            reversi.Reversal(reversi.wave - 2);
            wave_old = reversi.wave;
        }
        if (reversi.HaveOK() == 1)
            reversi.wave++;

        reversi.ClearOK();
        reversi.JudgeBoard(reversi.wave);
        reversi.JudgeBoard(reversi.wave);//二次虛擬判別(OK用)
        (reversi.wave % 2 == 1) ? reversi.AICount(0, reversi.wave) : reversi.AICount(1, reversi.wave);
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
            setpage();
        }
        else if (result == 4)//悔棋
        {
            reversi.regret_chess(reversi.wave);
        }
        else if (result == 5)//右鍵(>=4)
        {
            reversi.RightButtom(reversi.wave, MouseX, MouseY);
        }
    }
    if (game)
    {
        printf("\33[?25l");

        printf("\33[12;0H黑棋有:%d顆\n白棋有:%d顆\n", reversi.CountBoard(BLACK), reversi.CountBoard(WHITE));
        if (reversi.CountBoard(BLACK) > reversi.CountBoard(WHITE))
            printf("黑方獲勝\n");
        else if (reversi.CountBoard(BLACK) < reversi.CountBoard(WHITE))
            printf("白方獲勝\n");
        else
            printf("雙方平手\n");
        printf("╔═════╗");
        printf("\n║ 繼續║");
        printf("\n╚═════╝\n");

        while (true)
        {
            Mouse mouse_win;
            uint8_t result = mouse_win.MouseTracking("win");
            
            if (result == 0)break;
        }
        if (reversi.CountBoard(BLACK) > reversi.CountBoard(WHITE))
        {
            for (short i = 0; i < BOARD_SIZE * 5; i++)
            {
                for (short j = 0; j < BOARD_SIZE * 4; j++)
                    printf("\33[%d;%dH○", j, i * 2);

                Sleep(50);
            }
        }
        else if (reversi.CountBoard(BLACK) < reversi.CountBoard(WHITE))
        {
            for (short i = 0; i < BOARD_SIZE * 5; i++)
            {
                for (short j = 0; j < BOARD_SIZE * 4; j++)
                    printf("\33[%d;%dH●", j, i * 2);

                Sleep(50);
            }
        }
        else
        {
            for (short i = 0; i < BOARD_SIZE * 5; i++)
            {
                for (short j = 0; j < BOARD_SIZE + 5; j++)
                    printf("\33[%d;%dH˙", j, i * 2);

                Sleep(50);
            }
        }
    }

    if (!game)
    {
        setpage();
        copy_Number_of_executions = set.Number_of_executions;
        /*SetCursorPos(GetSystemMetrics(SM_CXSCREEN) * 0.5, GetSystemMetrics(SM_CYSCREEN) * 0.2);//移動滑鼠
        Sleep(25);
        mouse.MouseTracking("AI");
        Sleep(25);*/
        system("cls");//清除終端
        printf("\33[10;1H延遲  :%5dms", set.delar_time);
    }

    SYSTEMTIME currentTime; // 定義 SYSTEMTIME 結構體變數用於儲存目前時間
    int timeCounter = 0; // 定義計數器變數

    GetLocalTime(&currentTime);// 取得目前本地時間
    int oldSecond = currentTime.wSecond; // 儲存舊的秒數
    int FPS = 0;

    while (!game && copy_Number_of_executions>0)
    {
        reversi.CreateBoard();//創建棋盤
        reversi.JudgeBoard(reversi.wave);
        reversi.ClearOK();
        reversi.CopyBoard(reversi.wave);

        

        while (true)
        {
            FPS++;
            reversi.JudgeBoard(reversi.wave);
            if (wave_old != reversi.wave)//移除翻棋才再翻棋的可能(同回合重複翻棋)
            {
                reversi.Reversal(reversi.wave - 2);
                wave_old = reversi.wave;
            }
            if (reversi.HaveOK() == 1)
                reversi.wave++;

            reversi.ClearOK();
            reversi.JudgeBoard(reversi.wave);
            reversi.JudgeBoard(reversi.wave);//二次虛擬判別(OK用)
            (reversi.wave % 2 == 1) ? reversi.AICount(0, reversi.wave) : reversi.AICount(1, reversi.wave);
            //reversi.ShowBoard(reversi.wave);//顯示棋盤
            printf("\33[1;1HWave:%3d", reversi.wave);

            reversi.CopyBoard(reversi.wave);

            if (reversi.wave % 2 == 1)
                reversi.wave += reversi.AIPut(BLACK);
            else
                reversi.wave += reversi.AIPut(WHITE);

            if (reversi.Ending(reversi.wave) == 1)
                break;

            Sleep(set.delar_time);

            GetLocalTime(&currentTime);
            
            if (currentTime.wSecond == oldSecond + 1) // 如果新的秒數比舊的秒數大 1，則增加計數
            {
                timeCounter++;
                printf("\33[7;1HFPS   :%5d", FPS);
                FPS = 0;
            }
            
            oldSecond = currentTime.wSecond;// 更新舊的秒數

            printf("\33[8;1H花費時間: %02dm:%02ds\n", timeCounter / 60, timeCounter % 60);
        }
        printf("\33[2;1Htimes:%5d/%5d", copy_Number_of_executions, set.Number_of_executions);
        printf("\33[3;1H共    :%5d局", ++all_win);
        if (reversi.CountBoard(BLACK) > reversi.CountBoard(WHITE))
        {
            printf("\33[4;1H白棋贏:%5d(%3.4f%%) ", ++white_win, static_cast<double>(white_win) / all_win*100);
        }
        else if (reversi.CountBoard(BLACK) < reversi.CountBoard(WHITE))
        {
            printf("\33[5;1H黑棋贏:%5d(%3.4f%%) ", ++black_win, static_cast<double>(black_win) / all_win * 100);
        }
        else
        {
            printf("\33[6;1H平局  :%5d(%3.4f%%)", ++draw, static_cast<double>(draw) / all_win * 100);
        }
        
        reversi.wave = 1;
        copy_Number_of_executions--;



        

        
            // 取得目前本地時間
        

        std::string board_folderPath = "./boards";// 資料夾路徑
        if (_access(board_folderPath.c_str(), 0) != 0) // 檢查資料夾是否存在，如果不存在就創建
            _mkdir(board_folderPath.c_str());

        std::ofstream outFile("./boards/123.txt", std::ios::binary);// 打開二進位檔案

        if (outFile.is_open()) // 檢查是否成功打開檔案
        {
            outFile
                << "局:" << all_win << ' '
                << "\n白棋贏:" << white_win << ' '
                << "\n黑棋贏:" << black_win << ' '
                << "\n平局  :" << draw << ' '
                << std::endl;

            outFile.close();
        }
    
    }
    if (!game)
    {
        printf("\33[7;1H╔");
        printf("═════");
        printf("╗");
        printf("\33[8;1H║ 繼續║");
        printf("\33[9;1H╚");
        printf("═════");
        printf("╝\n");

        Mouse mouse_ai_win;
        uint8_t result = mouse_ai_win.MouseTracking("ai_win");
    }
    system("cls");//清除終端
    SetCursorPos(GetSystemMetrics(SM_CXSCREEN) * 0.5, GetSystemMetrics(SM_CYSCREEN) * 0.45);//移動滑鼠

    Mouse mouse_end;
    end = mouse_end.MouseTracking("end");
    if (end)
        main();

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

void setpage()
{
    Set set;
    system("cls");
    FontSize(21, 28);//字體大小
    set.set_up();

    set.LoadSetFile("boards", "Jerry.board_set");
    while (true)
    {
        Mouse mouse_set;
        uint8_t re = mouse_set.MouseTracking("set");
        char filename[64] = "Jerry";
        set.SaveSetFile(filename);
        set.set_up();
        if (re == 1)break;
        else if (re == 2)set.reset();
        
        set.set_up();//還原後及時更新
    }
    FontSize(30 / size, 40 / size);//字體大小
    system("cls");
}
