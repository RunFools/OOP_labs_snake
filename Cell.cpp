#include "Cell.h"
#include "CellType.h"

Cell::Cell(int x, int y, int color, char ch, CellType type) :
    x(x),
    y(y),
    color(color),
    ch(ch),
    type(type) {}

int Cell::getX() const { return x;}
int Cell::getY() const { return y; }
int Cell::getColor() const { return color; }
char Cell::getChar() const { return ch; }
CellType Cell::getType() const { return type; }

void Cell::setColor(int color) { this->color = color; }
void Cell::setChar(char ch) { this->ch = ch; }
