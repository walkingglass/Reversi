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
    // 獲取主顯示器的寬度和高度
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // 獲取主顯示器的句柄
    HWND hWnd = GetDesktopWindow();

    // 設置窗口樣式為全螢幕
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);

    // 設置窗口位置和大小
    SetWindowPos(hWnd, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_SHOWWINDOW);

    // 顯示全螢幕窗口
    ShowWindow(hWnd, SW_MAXIMIZE);
}