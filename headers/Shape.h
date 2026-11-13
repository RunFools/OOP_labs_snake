#pragma once

#include <windows.h>
#include "Cell.h"

class Shape {
private:
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

protected:
    void drawCell(Cell cell);
};