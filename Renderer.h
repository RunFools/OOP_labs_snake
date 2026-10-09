#pragma once

#include <windows.h>
#include "Snake.h"

class Renderer {
private:
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    void drawCell(short x, short y, wchar_t ch, WORD color);

public:
    void init(HANDLE hOut);
    void drawSnake(Cell cell);
    void drawEmpty(Cell cell);
    void drawEmpty(short x, short y);
};