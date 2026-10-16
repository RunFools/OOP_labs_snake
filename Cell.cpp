#include "Cell.h"
#include "CellType.h"

Cell::Cell(short x, short y, short color, char ch, CellType type) :
    x(x),
    y(y),
    color(color),
    ch(ch),
    type(type) {}

short Cell::getX() const { return x;}
short Cell::getY() const { return y; }
short Cell::getColor() const { return color; }
char Cell::getChar() const { return ch; }
CellType Cell::getType() const { return type; }

void Cell::setColor(short color) { this->color = color; }
void Cell::setChar(char ch) { this->ch = ch; }
