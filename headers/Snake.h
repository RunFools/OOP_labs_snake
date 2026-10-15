#pragma once

#include <deque>
#include <array>
#include "Cell.h"

class Snake {
private:
    std::deque<Cell> body;

    bool epileptionMode = false;
    bool moveUpFlag = false;
    bool isLongEnough = false;

    std::array<char, 26> letters {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

public:
    Snake(bool epileptionMode);

    int getSize() const;
    Cell getHead() const;
    Cell getTail() const;

    void setEpileptionMode(bool epileptionMode);
    void setLongEnough(bool isLongEnough);

    void addHead(int x, int y);
    void moveLeft();

};