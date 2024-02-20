#ifndef MOUSE_H
#define MOUSE_H

#include "Board.h"

#include <windows.h>

class Mouse
{
public:
    Mouse();
    ~Mouse(); // ���O���R�c��ơA�t�d����귽

    void setCursorPosition(short x, short y);
    void updateMousePosition(short x, short y);
    int getMouseX() const;  // �ϥ� const ��ܳo�O�@�Ө��o���������
    int getMouseY() const;
    int MouseTracking(const char* string);
    //void ScrollConsole(short lines);

private:
    HANDLE hIn;//��J�w�İϪ��y�`
    short mouseX;
    short mouseY;
    DWORD prevMode;
};

#endif // MOUSE_H
