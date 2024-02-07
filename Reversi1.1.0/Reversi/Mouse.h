// mouse.h
#ifndef MOUSE_H
#define MOUSE_H

#include "Board.h"

#include <windows.h>

class Mouse
{
public:
    Mouse();
    ~Mouse(); // ���O���R�c��ơA�t�d����귽

    void setCursorPosition(short int x, short int y);
    void updateMousePosition(short int x, short int y);
    int getMouseX() const;  // �ϥ� const ��ܳo�O�@�Ө��o���������
    int getMouseY() const;
    int MouseTracking(const char* show_string, short int show_x, short int show_y);
    int StartMouseTracking();
    int EndMouseTracking();
    int LoadMouseTracking();

private:
    HANDLE hIn;//��J�w�İϪ��y�`
    short int mouseX;
    short int mouseY;
    DWORD prevMode;
};

#endif // MOUSE_H
