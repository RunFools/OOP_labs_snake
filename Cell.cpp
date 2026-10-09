#include "Cell.h"
#include "CellType.h"

Cell::Cell(int x, int y, int color, wchar_t ch, CellType type) :
    x(x),
    y(y),
    color(color),
    ch(ch),
    type(type) {}

int Cell::getX() const { return x;}
int Cell::getY() const { return y; }
int Cell::getColor() const { return color; }
wchar_t Cell::getChar() const { return ch; }
CellType Cell::getType() const { return type; }

void Cell::setColor(int color) { this->color = color; }
void Cell::setChar(wchar_t ch) { this->ch = ch; }
