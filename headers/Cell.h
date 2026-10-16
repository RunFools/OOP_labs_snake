#pragma once

#include "CellType.h"

class Cell {
private:
    short x;
    short y;
    short color;
    char ch;
    CellType type;

public:
    Cell(short x, short y, short color, char ch, CellType type);

    short getX() const;
    short getY() const;
    short getColor() const;
    char getChar() const;
    CellType getType() const;

    void setColor(short color);
    void setChar(char ch);

};