#pragma once

#include "CellType.h"

class Cell {
private:
    int x;
    int y;
    int color;
    wchar_t ch;
    CellType type;

public:
    Cell(int x, int y, int color, wchar_t ch, CellType type);

    int getX() const;
    int getY() const;
    int getColor() const;
    wchar_t getChar() const;
    CellType getType() const;

    void setColor(int color);
    void setChar(wchar_t ch);

};