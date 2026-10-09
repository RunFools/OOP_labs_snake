#pragma once

#include "CellType.h"

class Cell {
private:
    int x;
    int y;
    int color;
    char ch;
    CellType type;

public:
    Cell(int x, int y, int color, char ch, CellType type);

    int getX() const;
    int getY() const;
    int getColor() const;
    char getChar() const;
    CellType getType() const;

    void setColor(int color);
    void setChar(char ch);

};