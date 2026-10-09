#include "Snake.h"
#include "Cell.h"
#include "CellType.h"
#include "Rand.h"

Snake::Snake() {};

int Snake::getSize() const { return body.size(); }
Cell Snake::getHead() const { return body.front(); }
Cell Snake::getTail() const { return body.back(); }

void Snake::setEpileptionMode(bool epileptionMode) { this->epileptionMode = epileptionMode; }
void Snake::setLongEnough(bool isLongEnough) { this->isLongEnough = isLongEnough; }

void Snake::addHead(int x, int y) {
    if(epileptionMode) {
        body.push_front(Cell(
            x,
            y, 
            Rand::getRandInt(2, 8),
            letters[Rand::getRandInt(0, 25)],
            CellType::Snake));
    } else {
        body.push_front(Cell(
            x,
            y, 
            7,
            letters[Rand::getRandInt(0, 25)],
            CellType::Snake));
    }
}

void Snake::moveLeft() {
        if (body.front().getX() != 0) {
            if (moveUpFlag) {
                if(epileptionMode) {
                    body.push_front(Cell(
                    body.front().getX() - 1,
                    body.front().getY() + 1,
                    Rand::getRandInt(2, 8),
                    letters[Rand::getRandInt(0, 25)],
                    CellType::Snake));
                } else {
                    body.push_front(Cell(
                    body.front().getX() - 1,
                    body.front().getY() + 1,
                    7,
                    letters[Rand::getRandInt(0, 25)],
                    CellType::Snake));
                }

                moveUpFlag = false;

        } else {
            if(epileptionMode) {
                body.push_front(Cell(
                body.front().getX() - 1,
                body.front().getY() - 1,
                Rand::getRandInt(2, 8),
                letters[Rand::getRandInt(0, 25)],
                CellType::Snake));
            } else {
                body.push_front(Cell(
                body.front().getX() - 1,
                body.front().getY() - 1,
                7,
                letters[Rand::getRandInt(0, 25)],
                CellType::Snake));
            }

            moveUpFlag = true;
        }
    }

    if(isLongEnough) { body.pop_back(); }
}
