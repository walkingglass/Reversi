#include <windows.h>
#include <iostream>
#include <string>

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// ���o�зǿ�X���y�`

static void FontSize(int FontSizeX, int FontSizeY)
{
    // ���o��e�r��T��
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

    // �]�w�s���r��j�p
    fontInfo.dwFontSize.X = FontSizeX; // �]�w�e��
    fontInfo.dwFontSize.Y = FontSizeY; // �]�w����

    // �M�ηs���r��j�p
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

static void WindowSize(int Right, int Bottom)
{
    // ���o�ثe������T
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

    // �]�w�s�������j�p
    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = Right; // �]�w�����k���
    windowSize.Bottom = Bottom; // �]�w���������

    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // �]�w�w�İϤj�p�H�A���s�������j�p
    COORD bufferSize;
    bufferSize.X = 80; // �]�w�w�İϼe��
    bufferSize.Y = 25; // �]�w�w�İϰ���

    SetConsoleScreenBufferSize(hConsole, bufferSize);
}

static void FullScreen()
{
    // ����D��ܾ����e�שM����
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // ����D��ܾ����y�`
    HWND hWnd = GetDesktopWindow();

    // �]�m���f�˦������ù�
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);

    // �]�m���f��m�M�j�p
    SetWindowPos(hWnd, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_SHOWWINDOW);

    // ��ܥ��ù����f
    ShowWindow(hWnd, SW_MAXIMIZE);
}