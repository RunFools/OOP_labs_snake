#include <windows.h>
#include "Snake.h"
#include "Cell.h"
#include "CellType.h"
#include "Rand.h"

const int LEFT_X = 0;
const int RIGHT_X = 119;
const int TOP_Y = 0;
const int BOTTOM_Y = 29;

Snake::Snake(int speed, int maxSize, bool epileptionMode) : speed(speed), maxSize(maxSize), lastMoveTime(0), epileptionMode(epileptionMode) {};

int Snake::getSpeed() const { return speed; }
int Snake::getSize() const { return body.size(); }
ULONGLONG Snake::getLastMoveTimes() const { return lastMoveTime; }
Cell Snake::getHead() const { return body.front(); }
Cell Snake::getTail() const { return body.back(); }

void Snake::setEpileptionMode(bool epileptionMode) { this->epileptionMode = epileptionMode; }

void Snake::addHead(int x, int y, std::queue<Cell>& renderQueue) {
    if(epileptionMode) {
        body.push_front(Cell(
            x,
            y, 
            Rand::getRandInt(2, 8),
            letters[Rand::getRandInt(0, 25)],
            CellType::Snake)
        );
    } else {
        body.push_front(Cell(
            x,
            y, 
            7,
            letters[Rand::getRandInt(0, 25)],
            CellType::Snake)
        );
    }
    renderQueue.push(body.front());
}

void Snake::moveLeft(std::queue<Cell>& renderQueue) {
        if (body.front().getX() == 0) {
            touchedBorderFlag = true;
        } else {
            if (moveUpFlag) {
                addHead(body.front().getX() - 1, body.front().getY() + 1, renderQueue);
                moveUpFlag = false;
            } else {
                addHead(body.front().getX() - 1, body.front().getY() - 1, renderQueue);
                moveUpFlag = true;
            }
            renderQueue.push(body.front());
        }

        if(touchedBorderFlag || body.size() > maxSize) {
            body.back().setChar(' ');
            body.back().setColor(0);
            renderQueue.push(std::move(body.back()));
            body.pop_back();
        }

        if(body.size() == 0) {
            addHead(RIGHT_X, Rand::getRandInt(TOP_Y + 1, BOTTOM_Y - 1), renderQueue);
            touchedBorderFlag = false;
        }

        lastMoveTime = GetTickCount64();
}
