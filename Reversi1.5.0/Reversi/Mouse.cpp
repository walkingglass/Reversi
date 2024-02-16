#include "mouse.h"
#include <windows.h>
#include "WindowsAPI.h"
#include <iostream>
#include "Set.h"
#include <string> 
#include <conio.h> // for _kbhit and _getch on Windows

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

int Mouse::MouseTracking(const char* string)
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
                    short mouseX = mouseEvent.dwMousePosition.X;//�ƹ�X��m
                    short mouseY = mouseEvent.dwMousePosition.Y;//�ƹ�Y��m

                    if (strcmp(string, "main") == 0)
                    {
                        if (mouseEvent.dwEventFlags == MOUSE_MOVED)//�ƹ�����
                        {
                            setCursorPosition(0, 4 + BOARD_SIZE);
                            if (set_mouse.Mouse_movement_display == true)
                                printf("(�Y�ɷƹ�) X = %3d, Y = %3d\33[?25l\n", mouseEvent.dwMousePosition.X, mouseEvent.dwMousePosition.Y);//���å���

                            updateMousePosition(mouseEvent.dwMousePosition.X / 2 - 1, mouseEvent.dwMousePosition.Y - 1);//���F�ŦX�Ѥl��l���B��
                        }
                        else if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//�ƹ�����
                        {


                            if (mouseX >= BOARD_SIZE * 2 + 6 && mouseY >= 0 && mouseX <= BOARD_SIZE * 2 + 11 && mouseY <= 2)return 1;
                            if (mouseX >= BOARD_SIZE * 2 + 6 && mouseY >= 3 && mouseX <= BOARD_SIZE * 2 + 11 && mouseY <= 5)return 2;
                            if (mouseX >= BOARD_SIZE * 2 + 6 && mouseY >= 6 && mouseX <= BOARD_SIZE * 2 + 11 && mouseY <= 8)return 3;
                            return 0;
                        }
                        else if (mouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//�ƹ��k��
                        {
                            return 4;

                        }
                    }
                    if (strcmp(string, "set") == 0)
                    {
                        if (mouseEvent.dwEventFlags == MOUSE_MOVED)//�ƹ�����
                        {
                            setCursorPosition(36, 0);
                            if (set_mouse.Mouse_movement_display == true)
                                printf("(�Y�ɷƹ�) X = %3d, Y = %3d\33[?25l\n", mouseEvent.dwMousePosition.X, mouseEvent.dwMousePosition.Y);//���å���
                        }
                        else if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//�ƹ�����
                        {

                            if (mouseX >= 1 && mouseX <= 6 && mouseY >= 0 && mouseY <= 2)return 1;
                            if (mouseX >= 10 && mouseX <= 19 && mouseY >= 0 && mouseY <= 2)exit(0);
                            //if(mouseX >=  && mouseX <=  && mouseY ==  )
                            if(mouseX >= 21 && mouseX <= 26 )
                            { 
                                if (mouseY == 3)set_mouse.Player_A = PLAYER;
                                else if (mouseY == 4)set_mouse.Player_B = PLAYER;
                            }
                            if (mouseX >= 29 && mouseX <= 30)
                            {
                                if (mouseY == 3)set_mouse.Player_A = AI;
                                else if (mouseY == 4)set_mouse.Player_B = AI;
                            }

                            if (mouseX >= 30 && mouseX <= 45 && mouseY >= 5 && mouseY <= 9)
                            {
                                uint8_t* option[] = { &set_mouse.Background_color, &set_mouse.Player_A_color, &set_mouse.Player_B_color, &set_mouse.hint_chess_color, &set_mouse.empty_chess_color };

                                for (uint8_t Array = 0; Array <= 6; Array++)
                                    if (mouseY == Array + 5)
                                        for (uint8_t i = 0; i < 16; i++) 
                                            if (mouseX == i + 30 || mouseX == i + 31) 
                                            {
                                                *(option[Array]) = i / 2 + 30; // �ഫ�r�C��
                                                if (mouseY == 5) *(option[Array]) += 10;//set_mouse.Background_color (�I���C��+10)
                                            }
                            }
                            if (mouseX >= 17 && mouseX <= 23 && mouseY >= 10 && mouseY <= 16)
                            {
                                printf("\33[%d;18H       ", mouseY+1);
                                printf("\33[3;50H               ");

                                std::string inputString;
                                short* option[] = { &set_mouse.normal_point, &set_mouse.bonus_point, &set_mouse.penalty_point, &set_mouse.distance_point ,&set_mouse.distance_point_variation ,&set_mouse.delar_time };

                                while (true) 
                                {
                                    if (_kbhit()) // �ˬd�O�_����L��J
                                    { 
                                        char inputChar = _getch(); // �����L��J
                                        if (inputChar == '\r' || inputString.size() > 5)
                                            break;
                                        if (mouseY >= 10 && mouseY <= 15)
                                        { 
                                            if (inputString.size() == 0)
                                            {
                                                if (inputChar == '+' || inputChar == '-' || std::isdigit(inputChar))  // �T�{��J�r�ŬO���Ī��Ʀr�r�ũΪ̥��t��
                                                {
                                                    inputString += inputChar; // �N�r�Űl�[��r�ꤤ
                                                    printf("\33[%d;25H\33[%dD", mouseY + 1, inputString.size());
                                                    std::cout << inputString << std::flush; // �M���e�@�ӿ�X����ܾ�Ӧr��
                                                }
                                            }
                                            else
                                            { 
                                                if (std::isdigit(inputChar))  // �T�{��J�r�ŬO���Ī��Ʀr�r�ũΪ̥��t��
                                                {
                                                    inputString += inputChar; // �N�r�Űl�[��r�ꤤ
                                                    printf("\33[%d;25H\33[%dD", mouseY + 1, inputString.size());
                                                    std::cout << inputString << std::flush; // �M���e�@�ӿ�X����ܾ�Ӧr��
                                                }
                                            }
                                        }
                                        else if (mouseY == 16)
                                        {
                                            if (inputString.size() == 1)
                                            {
                                                if (inputChar == '.' || std::isdigit(inputChar))  // �T�{��J�r�ŬO���Ī��Ʀr�r�ũΪ̥��t��
                                                {
                                                    inputString += inputChar; // �N�r�Űl�[��r�ꤤ
                                                    printf("\33[%d;25H\33[%dD", mouseY + 1, inputString.size());
                                                    std::cout << inputString << std::flush; // �M���e�@�ӿ�X����ܾ�Ӧr��
                                                }
                                            }
                                            else
                                            {
                                                if (std::isdigit(inputChar))  // �T�{��J�r�ŬO���Ī��Ʀr�r�ũΪ̥��t��
                                                {
                                                    inputString += inputChar; // �N�r�Űl�[��r�ꤤ
                                                    printf("\33[%d;25H\33[%dD", mouseY + 1, inputString.size());
                                                    std::cout << inputString << std::flush; // �M���e�@�ӿ�X����ܾ�Ӧr��
                                                }
                                            }
                                        }
                                    }
                                }

                                if (mouseY >= 10 && mouseY <= 15)
                                { 
                                    if (std::stoi(inputString) >= -32768 && std::stoi(inputString) <= 32767)
                                    {
                                        *(option[mouseY - 10]) = std::stoi(inputString);
                                        printf("\33[3;50H\33[32m��令�\ �w�x�s\33[0m");

                                    }
                                    else
                                        printf("\33[3;50H\33[31m��J���~\33[0m");
                                }
                                else if (mouseY == 16)
                                {
                                    if (std::stod(inputString) >= 0 && std::stod(inputString) <= 1)
                                    {
                                        set_mouse.random = std::stod(inputString);
                                        printf("\33[3;50H\33[32m��令�\ �w�x�s\33[0m");

                                    }
                                    else
                                        printf("\33[3;50H\33[31m��J���~\33[0m");
                                }

                            }

                            if (mouseX >= 25 && mouseX <= 28)
                            {
                                bool* option[] = { &set_mouse.Mouse_movement_display, &set_mouse.Mouse_right_display, &set_mouse.AI_skip, &set_mouse.hint_chess_open };

                                for (uint8_t y = 17; y <= 20; y++)
                                    if (mouseY == y)
                                        *option[y - 17] = true;

                            }
                            if (mouseX >= 31 && mouseX <= 35)
                            {
                                bool* option[] = { &set_mouse.Mouse_movement_display, &set_mouse.Mouse_right_display, &set_mouse.AI_skip, &set_mouse.hint_chess_open };

                                for (uint8_t y = 17; y <= 20; y++)
                                    if (mouseY == y)
                                        *option[y - 17] = false;

                            }

                            return -1;
                        }
                        else if (mouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//�ƹ��k��
                        {
                            return 4;

                        }
                    }
                    if ((strcmp(string, "start") == 0)||(strcmp(string, "end") == 0))
                    {
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

                        if (strcmp(string, "start") == 0)
                        {
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
                        else//end
                        {
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

                            setCursorPosition(Width * 0.48 - 10 * pow(Width * 0.48, -1) - 2, Height * 0.25);//�L���Y�p�ù����n��
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
                                if ((mouseX <= (Width * 0.7 + 1) && mouseX >= (Width * 0.3 - 1)) && (mouseY <= (Height * 0.4) && mouseY >= (Height * 0.1)))
                                {
                                    return 1;
                                }
                                if ((mouseX <= (Width * 0.7 + 1) && mouseX >= (Width * 0.3 - 1)) && (mouseY <= (Height * 0.9) && mouseY >= (Height * 0.6)))
                                {
                                    return 0;
                                }

                            }
                        }
                    }
                    if (strcmp(string, "win") == 0)
                    {
                        if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//�ƹ�����
                        {
                            if (mouseX >= BOARD_SIZE * 2 + 6 && mouseY >= 6 && mouseX <= BOARD_SIZE * 2 + 11 && mouseY <= 8)return 1;
                            if (mouseX >= 0 && mouseY >= 14 && mouseX <= 5 && mouseY <= 16)return 0;
                        }
                    }
                    if (strcmp(string, "load") == 0)
                    {
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
}


//void Mouse::ScrollConsole(short lines)
//{
//    // ����зǿ�X����x���B�z
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    // �������x�̹��w�İϪ���T
//    GetConsoleScreenBufferInfo(hConsole, &csbi);
//
//    // �������x�̹��w�İϪ��j�p
//    COORD bufferSize = csbi.dwSize;
//
//    // �������x�̹��w�İϪ������j�p
//    SMALL_RECT windowRect = csbi.srWindow;
//
//    // �p��s��������m
//    windowRect.Top += lines;
//    windowRect.Bottom += lines;
//
//    // �N��������b�̹��w�İϪ��d��
//    if (windowRect.Top < 0) {
//        windowRect.Top = 0;
//    }
//    if (windowRect.Bottom >= bufferSize.Y) {
//        windowRect.Bottom = bufferSize.Y - 1;
//    }
//
//    // �]�w�s��������m
//    SetConsoleWindowInfo(hConsole, TRUE, &windowRect);
//
//    // �N����x���в��ʨ���������W��
//    COORD cursorPos = { 0, 0 };
//    SetConsoleCursorPosition(hConsole, cursorPos);
//}

