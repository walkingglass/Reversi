#ifndef MOUSE_H
#define MOUSE_H

#include "Board.h"

#include <windows.h>

class Mouse
{
public:
    Mouse();
    ~Mouse(); // 類別的析構函數，負責釋放資源

    void setCursorPosition(short x, short y);
    void updateMousePosition(short x, short y);
    int getMouseX() const;  // 使用 const 表示這是一個取得成員的函數
    int getMouseY() const;
    int MouseTracking(const char* string);
    //void ScrollConsole(short lines);

private:
    HANDLE hIn;//輸入緩衝區的句柄
    short mouseX;
    short mouseY;
    DWORD prevMode;
};

#endif // MOUSE_H
