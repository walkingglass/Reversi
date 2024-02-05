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

    void setCursorPosition(int x, int y);
    void updateMousePosition(int x, int y);
    int getMouseX() const;  // �ϥ� const ��ܳo�O�@�Ө��o���������
    int getMouseY() const;
    int MouseTracking(const char* show_string, int show_x, int show_y);
    int StartMouseTracking();
    int EndMouseTracking();
    int LoadMouseTracking();

private:
    HANDLE hIn;//��J�w�İϪ��y�`
    int mouseX;
    int mouseY;
    DWORD prevMode;
};

#endif // MOUSE_H
