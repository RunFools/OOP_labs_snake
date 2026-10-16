#pragma once

#include <queue>
#include <deque>
#include <array>
#include "Cell.h"

class Snake {
private:
    inline static const std::array<char, 26> letters {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    std::deque<Cell> body;

    int speed;
    int maxSize;
    ULONGLONG lastMoveTime;
    bool epileptionMode = false;
    bool moveUpFlag = false;
    bool touchedBorderFlag = false;

public:
    Snake(int speed, int maxSize, bool epileptionMode);

    int getSpeed() const;
    int getSize() const;
    ULONGLONG getLastMoveTimes() const;
    Cell getHead() const;
    Cell getTail() const;

    void setEpileptionMode(bool epileptionMode);
    void setLongEnough(bool isLongEnough);

    void addHead(int x, int y, std::queue<Cell>& renderQueue);
    void moveLeft(std::queue<Cell>& renderQueue);

};