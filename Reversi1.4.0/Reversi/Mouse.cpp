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
    INPUT_RECORD irInBuf[128]; //�x�s��J�ƥ�O�����w�İ�
    DWORD cNumRead;//����Ū�����ƥ��

    while (true)//�@���bŪ��
    {
        if (ReadConsoleInput(hIn, irInBuf, 128, &cNumRead))//Ū������x��J�ƥ�
        {
            for (DWORD i = 0; i < cNumRead; i++)//�M��Ū���쪺�ƥ�O��
            {
                if (irInBuf[i].EventType == MOUSE_EVENT)//�P�_�ثe�ƥ�O�_���ƹ��ƥ�
                {
                    MOUSE_EVENT_RECORD mouseEvent = irInBuf[i].Event.MouseEvent;//�ƹ��ƥ�
                    if (mouseEvent.dwEventFlags == MOUSE_MOVED)//�ƹ�����
                    {
                        //���F�ŦX�Ѥl��l���B��
                        short mouseX = mouseEvent.dwMousePosition.X / 2 - 1;
                        short mouseY = mouseEvent.dwMousePosition.Y - 1;

                        setCursorPosition(show_x, show_y);
                        if (set_mouse.Mouse_movement_display == true && show_string != "")
                            printf("(�Y��)%s X = %3d, Y = %3d\33[?25l\n", show_string, mouseEvent.dwMousePosition.X, mouseEvent.dwMousePosition.Y);//���å���

                        updateMousePosition(mouseX, mouseY);
                    }
                    else if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//�ƹ�����
                    {
                        //�ƹ���m(���F�ŦX��l���B��)
                        short mouseX = mouseEvent.dwMousePosition.X;
                        short mouseY = mouseEvent.dwMousePosition.Y;

                        if (mouseX >= BOARD_SIZE * 2 + 6 && mouseY >= 0 && mouseX <= BOARD_SIZE * 2 + 11 && mouseY <= 2)return 2;
                        if (mouseX >= BOARD_SIZE * 2 + 6 && mouseY >= 3 && mouseX <= BOARD_SIZE * 2 + 11 && mouseY <= 5)return 3;
                        if (mouseX >= BOARD_SIZE * 2 + 6 && mouseY >= 6 && mouseX <= BOARD_SIZE * 2 + 11 && mouseY <= 8)return 4;
                        return 0;
                    }
                    else if (mouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//�ƹ��k��
                    {
                        return 1;
                    }
                }
            }
        }
    }
}


void ClearScreen() // �M������x�ù�
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);// ���o�зǿ�X���y�`
    COORD coord = { 0, 0 };// �]�w COORD ���c��A�Ω���w�M�����_�l��m�]0, 0�^
    DWORD count;// �Ω�O�s FillConsoleOutputCharacter ��ƪ���X�r����
    CONSOLE_SCREEN_BUFFER_INFO csbi;// �Ω�O�s CONSOLE_SCREEN_BUFFER_INFO ���c�骺����x�ù��w�İϫH��
    GetConsoleScreenBufferInfo(hStdOut, &csbi);// ���o����x�ù��w�İϫH��
    FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);// �ϥ� FillConsoleOutputCharacter ��ƱN��ӿù���R���Ů�r��
    SetConsoleCursorPosition(hStdOut, coord);// �]�w����x��Ц�m�� (0, 0)
}

int Mouse::StartMouseTracking()
{
    INPUT_RECORD irInBuf[128]; //�x�s��J�ƥ�O�����w�İ�
    DWORD cNumRead;//����Ū�����ƥ��

    while (true)//�@���bŪ��
    {
        if (ReadConsoleInput(hIn, irInBuf, 128, &cNumRead))//Ū������x��J�ƥ�
        {
            for (DWORD i = 0; i < cNumRead; i++)//�M��Ū���쪺�ƥ�O��
            {
                if (irInBuf[i].EventType == MOUSE_EVENT)//�P�_�ثe�ƥ�O�_���ƹ��ƥ�
                {
                    MOUSE_EVENT_RECORD mouseEvent = irInBuf[i].Event.MouseEvent;//�ƹ��ƥ�
                    int mouseX = mouseEvent.dwMousePosition.X;//�ƹ���m
                    int mouseY = mouseEvent.dwMousePosition.Y;



                    //***********************************************************************************************************

                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// ���o�зǿ�X���y�`
                    CONSOLE_FONT_INFOEX fontInfo;// �w�q CONSOLE_FONT_INFOEX ���c��A�Ω��x�s�ثe�r��T��
                    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
                    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);// ���o��e�r��T��

                    COORD fontSize = fontInfo.dwFontSize;// ���o�r��j�p�H��
                    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;// �w�q CONSOLE_SCREEN_BUFFER_INFO ���c��A�Ω��x�s����x�ù��w�İϰT��

                    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);// ���o����x�ù��w�İϫH�� 

                    HWND consoleWindow = GetConsoleWindow();// ���o����x�����y�`
                    RECT consoleRect;// �w�q RECT ���c��A�Ω��x�s����x�����x�θ�T

                    if (GetWindowRect(consoleWindow, &consoleRect))// ���o����x�����x�ΫH�� 
                    {
                        // �p�ⱱ��x�e�שM���ס]�����^
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
                    printf("��");

                    setCursorPosition(Width * 0.3, Height * 0.3);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("��");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.3);
                    printf("��");

                    setCursorPosition(Width * 0.3 - 1, Height * 0.6);
                    printf("��");

                    setCursorPosition(Width * 0.3, Height * 0.6);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("��");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.6);
                    printf("��");

                    setCursorPosition(Width * 0.48, Height * 0.45);
                    printf("�¥մ�");

                    setCursorPosition(Width * 0.432 + Width * Width * 0.0001f, Height * 0.75);//�L�թ�j�ù����n��
                    printf("\33[5m�I��\33[34m���D\33[0m\33[5m�}�l�C��\33[0m");

                    if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)//�ƹ�����
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ���o�зǿ�X���y�`
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo; // �w�q����x�ù��w�İϪ��H�����c

    if (GetConsoleScreenBufferInfo(hConsole, &bufferInfo)) // ���o����x�ù��w�İϫH�� 
    {
        SetCursorPos(GetSystemMetrics(SM_CXSCREEN)*0.5, GetSystemMetrics(SM_CYSCREEN)*0.45); //�ܤ��ƹ�
    }

    //CloseHandle(hConsole); // ��������x�y�`

    INPUT_RECORD irInBuf[128]; //�x�s��J�ƥ�O�����w�İ�
    DWORD cNumRead;//����Ū�����ƥ��

    while (true)//�@���bŪ��
    {
        if (ReadConsoleInput(hIn, irInBuf, 128, &cNumRead))//Ū������x��J�ƥ�
        {
            for (DWORD i = 0; i < cNumRead; i++)//�M��Ū���쪺�ƥ�O��
            {
                if (irInBuf[i].EventType == MOUSE_EVENT)//�P�_�ثe�ƥ�O�_���ƹ��ƥ�
                {
                    MOUSE_EVENT_RECORD mouseEvent = irInBuf[i].Event.MouseEvent;//�ƹ��ƥ�
                    short mouseX = mouseEvent.dwMousePosition.X;//�ƹ���m
                    short mouseY = mouseEvent.dwMousePosition.Y;



                    //***********************************************************************************************************

                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// ���o�зǿ�X���y�`
                    CONSOLE_FONT_INFOEX fontInfo;// �w�q CONSOLE_FONT_INFOEX ���c��A�Ω��x�s�ثe�r��T��
                    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
                    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);// ���o��e�r��T��

                    COORD fontSize = fontInfo.dwFontSize;// ���o�r��j�p�H��
                    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;// �w�q CONSOLE_SCREEN_BUFFER_INFO ���c��A�Ω��x�s����x�ù��w�İϰT��
                    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);// ���o����x�ù��w�İϫH�� 


                    HWND consoleWindow = GetConsoleWindow();// ���o����x�����y�`
                    RECT consoleRect;// �w�q RECT ���c��A�Ω��x�s����x�����x�θ�T

                    if (GetWindowRect(consoleWindow, &consoleRect))// ���o����x�����x�ΫH�� 
                    {
                        // �p�ⱱ��x�e�שM���ס]�����^
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
                    printf("��");

                    setCursorPosition(Width * 0.3, Height * 0.1);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("��");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.1);
                    printf("��");

                    setCursorPosition(Width * 0.3 - 1, Height * 0.4);
                    printf("��");

                    setCursorPosition(Width * 0.3, Height * 0.4);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("��");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.4);
                    printf("��");

                    setCursorPosition(Width * 0.48 - 10 * pow(Width * 0.48, -1) -2, Height * 0.25);//�L���Y�p�ù����n��
                    printf("�A�Ӥ@��");

                    setCursorPosition(Width * 0.3 - 1, Height * 0.6);
                    printf("��");

                    setCursorPosition(Width * 0.3, Height * 0.6);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("��");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.6);
                    printf("��");

                    setCursorPosition(Width * 0.3 - 1, Height * 0.9);
                    printf("��");

                    setCursorPosition(Width * 0.3, Height * 0.9);
                    for (int i = Width * 0.3; i < Width * 0.7; i++)
                        printf("��");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.9);
                    printf("��");

                    setCursorPosition(Width * 0.48 - 10 * pow(Width * 0.48, -1), Height * 0.75);//�L���Y�p�ù����n��
                    printf("����");

                    setCursorPosition(Width * 0.7 + 1, Height * 0.9);//�������T���@�Ӧ�m

                    if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)//�ƹ�����
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
    // ����зǿ�X����x���B�z
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    // �������x�̹��w�İϪ���T
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // �������x�̹��w�İϪ��j�p
    COORD bufferSize = csbi.dwSize;

    // �������x�̹��w�İϪ������j�p
    SMALL_RECT windowRect = csbi.srWindow;

    // �p��s��������m
    windowRect.Top += lines;
    windowRect.Bottom += lines;

    // �N��������b�̹��w�İϪ��d��
    if (windowRect.Top < 0) {
        windowRect.Top = 0;
    }
    if (windowRect.Bottom >= bufferSize.Y) {
        windowRect.Bottom = bufferSize.Y - 1;
    }

    // �]�w�s��������m
    SetConsoleWindowInfo(hConsole, TRUE, &windowRect);

    // �N����x���в��ʨ���������W��
    COORD cursorPos = { 0, 0 };
    SetConsoleCursorPosition(hConsole, cursorPos);
}



int Mouse::LoadMouseTracking()
{
    INPUT_RECORD irInBuf[128]; //�x�s��J�ƥ�O�����w�İ�
    DWORD cNumRead;//����Ū�����ƥ��

    GetConsoleMode(hIn, &cNumRead);
    SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    while (true)//�@���bŪ��
    {
        if (ReadConsoleInput(hIn, irInBuf, 128, &cNumRead))//Ū������x��J�ƥ�
        {
            for (DWORD i = 0; i < cNumRead; i++)//�M��Ū���쪺�ƥ�O��
            {
                if (irInBuf[i].EventType == MOUSE_EVENT)//�P�_�ثe�ƥ�O�_���ƹ��ƥ�
                {
                    MOUSE_EVENT_RECORD mouseEvent = irInBuf[i].Event.MouseEvent;//�ƹ��ƥ�
                    if (mouseEvent.dwEventFlags == MOUSE_MOVED)//�ƹ�����
                    {
                        //���F�ŦX�Ѥl��l���B��
                        int mouseX = mouseEvent.dwMousePosition.X / 2 - 1;
                        int mouseY = mouseEvent.dwMousePosition.Y - 1;

                        setCursorPosition(12, 0);
                        printf("(�Y��)�ƹ� X = %3d, Y = %3d\33[?25l\n", mouseEvent.dwMousePosition.X, mouseEvent.dwMousePosition.Y);//���å���


                        updateMousePosition(mouseX, mouseY);
                    }
                    else if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//�ƹ�����
                    {
                        //�ƹ���m(���F�ŦX��l���B��)
                        short mouseX = mouseEvent.dwMousePosition.X;
                        short mouseY = mouseEvent.dwMousePosition.Y;

                        if (mouseX >= 0 && mouseY >= 0 && mouseX <= 6 && mouseY <= 2)return 0;

                        for (short i = 0; i < 250; i++)if (mouseY == i)return i;
                        return -1;
                    }
                    else if (mouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//�ƹ��k��
                    {
                        return 1;
                    }
                }
            }
        }
    }

}
