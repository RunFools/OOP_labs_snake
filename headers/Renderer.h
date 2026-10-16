#pragma once

#include <windows.h>
#include "Snake.h"

class Renderer {
private:
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

public:
    void drawCell(Cell cell);
};