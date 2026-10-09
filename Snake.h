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

    std::array<wchar_t, 26> letters {
    L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H', L'I', 
    L'J', L'K', L'L', L'M', L'N', L'O', L'P', L'Q', L'R',
    L'S', L'T', L'U', L'V', L'W', L'X', L'Y', L'Z'
    };

public:
    Snake();

    int getSize() const;
    Cell getHead() const;
    Cell getTail() const;

    void setEpileptionMode(bool epileptionMode);
    void setLongEnough(bool isLongEnough);

    void addHead(int x, int y);
    void moveLeft();

};