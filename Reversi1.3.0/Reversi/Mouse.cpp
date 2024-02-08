#include "mouse.h"
#include <windows.h>
#include "WindowsAPI.h"
#include <iostream>
#include "Set.h"
Set set_mouse;

int Height = 0, Width = 0;
Board Mouse_reversi;

Mouse::Mouse()
{
    hIn = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hIn, &prevMode);
    SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    mouseX = 0;
    mouseY = 0;
}

Mouse::~Mouse()
{
    SetConsoleMode(hIn, prevMode);
}

void Mouse::setCursorPosition(short x, short y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Mouse::updateMousePosition(short x, short y)
{
    mouseX = x;
    mouseY = y;
}

int Mouse::getMouseX() const
{
    return mouseX;
}

int Mouse::getMouseY() const
{
    return mouseY;
}

int Mouse::MouseTracking(const char* show_string, short show_x, short show_y)
{
    INPUT_RECORD irInBuf[128]; //儲存輸入事件記錄的緩衝區
    DWORD cNumRead;//接收讀取的事件數

    while (true)//一直在讀取
    {
        if (ReadConsoleInput(hIn, irInBuf, 128, &cNumRead))//讀取控制台輸入事件
        {
            for (DWORD i = 0; i < cNumRead; i++)//遍歷讀取到的事件記錄
            {
                if (irInBuf[i].EventType == MOUSE_EVENT)//判斷目前事件是否為滑鼠事件
                {
                    MOUSE_EVENT_RECORD mouseEvent = irInBuf[i].Event.MouseEvent;//滑鼠事件
                    if (mouseEvent.dwEventFlags == MOUSE_MOVED)//滑鼠移動
                    {
                        //為了符合棋子格子的運算
                        short mouseX = mouseEvent.dwMousePosition.X / 2 - 1;
                        short mouseY = mouseEvent.dwMousePosition.Y - 1;

                        setCursorPosition(show_x, show_y);
                        if (set_mouse.Mouse_movement_display == true && show_string != "")
                            printf("(即時)%s X = %3d, Y = %3d\33[?25l\n", show_string, mouseEvent.dwMousePosition.X, mouseEvent.dwMousePosition.Y);//隱藏光標

                        updateMousePosition(mouseX, mouseY);
                    }
                    else if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//滑鼠左鍵
                    {
                        //滑鼠位置(為了符合格子的運算)
                        short mouseX = mouseEvent.dwMousePosition.X;
                        short mouseY = mouseEvent.dwMousePosition.Y;

                        if (mouseX >= BOARD_SIZE * 2 + 6 && mouseY >= 0 && mouseX <= BOARD_SIZE * 2 + 11 && mouseY <= 2)return 2;
                        if (mouseX >= BOARD_SIZE * 2 + 6 && mouseY >= 3 && mouseX <= BOARD_SIZE * 2 + 11 && mouseY <= 5)return 3;
                        if (mouseX >= BOARD_SIZE * 2 + 6 && mouseY >= 6 && mouseX <= BOARD_SIZE * 2 + 11 && mouseY <= 8)return 4;
                        return 0;
                    }
                    else if (mouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//滑鼠右鍵
                    {
                        return 1;
                    }
                }
            }
        }
    }
}


void ClearScreen() // 清除控制台螢幕
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);// 取得標準輸出的句柄
    COORD coord = { 0, 0 };// 設定 COORD 結構體，用於指定清除的起始位置（0, 0）
    DWORD count;// 用於保存 FillConsoleOutputCharacter 函數的輸出字元數
    CONSOLE_SCREEN_BUFFER_INFO csbi;// 用於保存 CONSOLE_SCREEN_BUFFER_INFO 結構體的控制台螢幕緩衝區信息
    GetConsoleScreenBufferInfo(hStdOut, &csbi);// 取得控制台螢幕緩衝區信息
    FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);// 使用 FillConsoleOutputCharacter 函數將整個螢幕填充為空格字符
    SetConsoleCursorPosition(hStdOut, coord);// 設定控制台游標位置為 (0, 0)
}

int Mouse::StartMouseTracking()
{
    INPUT_RECORD irInBuf[128]; //儲存輸入事件記錄的緩衝區
    DWORD cNumRead;//接收讀取的事件數

    while (true)//一直在讀取
    {
        if (ReadConsoleInput(hIn, irInBuf, 128, &cNumRead))//讀取控制台輸入事件
        {
            for (DWORD i = 0; i < cNumRead; i++)//遍歷讀取到的事件記錄
            {
                if (irInBuf[i].EventType == MOUSE_EVENT)//判斷目前事件是否為滑鼠事件
                {
                    MOUSE_EVENT_RECORD mouseEvent = irInBuf[i].Event.MouseEvent;//滑鼠事件
                    int mouseX = mouseEvent.dwMousePosition.X;//滑鼠位置
                    int mouseY = mouseEvent.dwMousePosition.Y;



                    //***********************************************************************************************************

                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// 取得標準輸出的句柄
                    CONSOLE_FONT_INFOEX fontInfo;// 定義 CONSOLE_FONT_INFOEX 結構體，用於儲存目前字體訊息
                    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
                    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);// 取得當前字體訊息

                    COORD fontSize = fontInfo.dwFontSize;// 取得字體大小信息
                    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;// 定義 CONSOLE_SCREEN_BUFFER_INFO 結構體，用於儲存控制台螢幕緩衝區訊息

                    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);// 取得控制台螢幕緩衝區信息 

                    HWND consoleWindow = GetConsoleWindow();// 取得控制台視窗句柄
                    RECT consoleRect;// 定義 RECT 結構體，用於儲存控制台視窗矩形資訊

                    if (GetWindowRect(consoleWindow, &consoleRect))// 取得控制台視窗矩形信息 
                    {
                        // 計算控制台寬度和高度（像素）
                        short consoleWidth = consoleRect.right - consoleRect.left;
                        short consoleHeight = consoleRect.bottom - consoleRect.top;


                        if (Height != consoleHeight / fontSize.Y || Width != consoleWidth / fontSize.X)
                            ClearScreen();

                        Height = consoleHeight / fontSize.Y;
                        Width = consoleWidth / fontSize.X;
                    }

                    //***********************************************************************************************************

                    printf("\33[?25l");

                    setCursorPosition(Width * 0.3 - 1, Height * 0.3);
                    printf("╔");

                    setCursorPosition(Width * 0.3, Height * 0.3);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("═");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.3);
                    printf("╗");

                    setCursorPosition(Width * 0.3 - 1, Height * 0.6);
                    printf("╚");

                    setCursorPosition(Width * 0.3, Height * 0.6);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("═");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.6);
                    printf("╝");

                    setCursorPosition(Width * 0.48, Height * 0.45);
                    printf("黑白棋");

                    setCursorPosition(Width * 0.432 + Width * Width * 0.0001f, Height * 0.75);//微調放大螢幕的歪斜
                    printf("\33[5m點擊\33[34m標題\33[0m\33[5m開始遊戲\33[0m");

                    if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)//滑鼠左鍵
                    {
                        if (mouseX< (Width * 0.7 + 1) && mouseX >(Width * 0.3 - 1))
                            if (mouseY< (Height * 0.6) && mouseY >(Height * 0.3))
                                return 0;
                    }
                }
            }
        }
    }
}


int Mouse::EndMouseTracking()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 取得標準輸出的句柄
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo; // 定義控制台螢幕緩衝區的信息結構

    if (GetConsoleScreenBufferInfo(hConsole, &bufferInfo)) // 取得控制台螢幕緩衝區信息 
    {
        SetCursorPos(GetSystemMetrics(SM_CXSCREEN)*0.5, GetSystemMetrics(SM_CYSCREEN)*0.45); //至中滑鼠
    }

    //CloseHandle(hConsole); // 關閉控制台句柄

    INPUT_RECORD irInBuf[128]; //儲存輸入事件記錄的緩衝區
    DWORD cNumRead;//接收讀取的事件數

    while (true)//一直在讀取
    {
        if (ReadConsoleInput(hIn, irInBuf, 128, &cNumRead))//讀取控制台輸入事件
        {
            for (DWORD i = 0; i < cNumRead; i++)//遍歷讀取到的事件記錄
            {
                if (irInBuf[i].EventType == MOUSE_EVENT)//判斷目前事件是否為滑鼠事件
                {
                    MOUSE_EVENT_RECORD mouseEvent = irInBuf[i].Event.MouseEvent;//滑鼠事件
                    short mouseX = mouseEvent.dwMousePosition.X;//滑鼠位置
                    short mouseY = mouseEvent.dwMousePosition.Y;



                    //***********************************************************************************************************

                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// 取得標準輸出的句柄
                    CONSOLE_FONT_INFOEX fontInfo;// 定義 CONSOLE_FONT_INFOEX 結構體，用於儲存目前字體訊息
                    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
                    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);// 取得當前字體訊息

                    COORD fontSize = fontInfo.dwFontSize;// 取得字體大小信息
                    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;// 定義 CONSOLE_SCREEN_BUFFER_INFO 結構體，用於儲存控制台螢幕緩衝區訊息
                    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);// 取得控制台螢幕緩衝區信息 


                    HWND consoleWindow = GetConsoleWindow();// 取得控制台視窗句柄
                    RECT consoleRect;// 定義 RECT 結構體，用於儲存控制台視窗矩形資訊

                    if (GetWindowRect(consoleWindow, &consoleRect))// 取得控制台視窗矩形信息 
                    {
                        // 計算控制台寬度和高度（像素）
                        short consoleWidth = consoleRect.right - consoleRect.left;
                        short consoleHeight = consoleRect.bottom - consoleRect.top;


                        if (Height != consoleHeight / fontSize.Y || Width != consoleWidth / fontSize.X)
                            ClearScreen();

                        Height = consoleHeight / fontSize.Y;
                        Width = consoleWidth / fontSize.X;
                    }

                    //***********************************************************************************************************

                    printf("\33[?25l");

                    setCursorPosition(Width * 0.3 - 1, Height * 0.1);
                    printf("╔");

                    setCursorPosition(Width * 0.3, Height * 0.1);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("═");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.1);
                    printf("╗");

                    setCursorPosition(Width * 0.3 - 1, Height * 0.4);
                    printf("╚");

                    setCursorPosition(Width * 0.3, Height * 0.4);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("═");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.4);
                    printf("╝");

                    setCursorPosition(Width * 0.48 - 10 * pow(Width * 0.48, -1) -2, Height * 0.25);//微調縮小螢幕的歪斜
                    printf("再來一局");

                    setCursorPosition(Width * 0.3 - 1, Height * 0.6);
                    printf("╔");

                    setCursorPosition(Width * 0.3, Height * 0.6);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("═");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.6);
                    printf("╗");

                    setCursorPosition(Width * 0.3 - 1, Height * 0.9);
                    printf("╚");

                    setCursorPosition(Width * 0.3, Height * 0.9);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("═");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.9);
                    printf("╝");

                    setCursorPosition(Width * 0.48 - 10 * pow(Width * 0.48, -1), Height * 0.75);//微調縮小螢幕的歪斜
                    printf("結束");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.9);//給關閉訊息一個位置

                    if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)//滑鼠左鍵
                    {
                        if ((mouseX<= (Width * 0.7 + 1) && mouseX >=(Width * 0.3 - 1)) && (mouseY<= (Height * 0.4) && mouseY >=(Height * 0.1)))
                        {
                            return 1;
                        }
                        if ((mouseX<= (Width * 0.7 + 1) && mouseX >=(Width * 0.3 - 1)) && (mouseY<= (Height * 0.9) && mouseY >=(Height * 0.6)))
                        {
                            return 0;
                        }
                        
                    }
                }
            }
        }
    }
}

void Mouse::ScrollConsole(short lines)
{
    // 獲取標準輸出控制台的處理
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    // 獲取控制台屏幕緩衝區的資訊
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // 獲取控制台屏幕緩衝區的大小
    COORD bufferSize = csbi.dwSize;

    // 獲取控制台屏幕緩衝區的視窗大小
    SMALL_RECT windowRect = csbi.srWindow;

    // 計算新的視窗位置
    windowRect.Top += lines;
    windowRect.Bottom += lines;

    // 將視窗限制在屏幕緩衝區的範圍內
    if (windowRect.Top < 0) {
        windowRect.Top = 0;
    }
    if (windowRect.Bottom >= bufferSize.Y) {
        windowRect.Bottom = bufferSize.Y - 1;
    }

    // 設定新的視窗位置
    SetConsoleWindowInfo(hConsole, TRUE, &windowRect);

    // 將控制台光標移動到視窗的左上角
    COORD cursorPos = { 0, 0 };
    SetConsoleCursorPosition(hConsole, cursorPos);
}



int Mouse::LoadMouseTracking()
{
    INPUT_RECORD irInBuf[128]; //儲存輸入事件記錄的緩衝區
    DWORD cNumRead;//接收讀取的事件數

    GetConsoleMode(hIn, &cNumRead);
    SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    while (true)//一直在讀取
    {
        if (ReadConsoleInput(hIn, irInBuf, 128, &cNumRead))//讀取控制台輸入事件
        {
            for (DWORD i = 0; i < cNumRead; i++)//遍歷讀取到的事件記錄
            {
                if (irInBuf[i].EventType == MOUSE_EVENT)//判斷目前事件是否為滑鼠事件
                {
                    MOUSE_EVENT_RECORD mouseEvent = irInBuf[i].Event.MouseEvent;//滑鼠事件
                    if (mouseEvent.dwEventFlags == MOUSE_MOVED)//滑鼠移動
                    {
                        //為了符合棋子格子的運算
                        int mouseX = mouseEvent.dwMousePosition.X / 2 - 1;
                        int mouseY = mouseEvent.dwMousePosition.Y - 1;

                        setCursorPosition(12, 0);
                        printf("(即時)滑鼠 X = %3d, Y = %3d\33[?25l\n", mouseEvent.dwMousePosition.X, mouseEvent.dwMousePosition.Y);//隱藏光標


                        updateMousePosition(mouseX, mouseY);
                    }
                    else if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//滑鼠左鍵
                    {
                        //滑鼠位置(為了符合格子的運算)
                        short mouseX = mouseEvent.dwMousePosition.X;
                        short mouseY = mouseEvent.dwMousePosition.Y;

                        if (mouseX >= 0 && mouseY >= 0 && mouseX <= 6 && mouseY <= 2)return 0;

                        for (short i = 0; i < 250; i++)if (mouseY == i)return i;
                        return -1;
                    }
                    else if (mouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//滑鼠右鍵
                    {
                        return 1;
                    }
                }
            }
        }
    }

}
