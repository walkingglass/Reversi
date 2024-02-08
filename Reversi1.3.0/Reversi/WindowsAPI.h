#include <windows.h>
#include <iostream>
#include <string>

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// 取得標準輸出的句柄

static void FontSize(int FontSizeX, int FontSizeY)
{
    // 取得當前字體訊息
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

    // 設定新的字體大小
    fontInfo.dwFontSize.X = FontSizeX; // 設定寬度
    fontInfo.dwFontSize.Y = FontSizeY; // 設定高度

    // 套用新的字體大小
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

static void WindowSize(int Right, int Bottom)
{
    // 取得目前視窗資訊
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

    // 設定新的視窗大小
    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = Right; // 設定視窗右邊界
    windowSize.Bottom = Bottom; // 設定視窗底邊界

    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // 設定緩衝區大小以適應新的視窗大小
    COORD bufferSize;
    bufferSize.X = 80; // 設定緩衝區寬度
    bufferSize.Y = 25; // 設定緩衝區高度

    SetConsoleScreenBufferSize(hConsole, bufferSize);
}

static void FullScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// 取得標準輸出裝置的終端處理碼

    CONSOLE_SCREEN_BUFFER_INFO csbi;// 獲取終端窗口信息
    GetConsoleScreenBufferInfo(hConsole, &csbi);//以終端窗口信息標準輸出裝置螢幕

    SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, 0);// 切換到全螢幕模式
}