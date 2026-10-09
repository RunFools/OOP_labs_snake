#include "Renderer.h"
#include "Rand.h"

void Renderer::drawCell(short x, short y, char ch, WORD color) {
    CHAR_INFO ci;
    ci.Char.UnicodeChar = ch;
    ci.Attributes = color;

    COORD      size   = { 1, 1 };
    COORD      origin = { 0, 0 };
    SMALL_RECT region = { x, y, x, y };

    WriteConsoleOutputW(hOut, &ci, size, origin, &region);
}

void Renderer::drawSnake(Cell cell) {
    drawCell(
        cell.getX(),
        cell.getY(),
        cell.getChar(),
        cell.getColor()
    );
}

void Renderer::drawEmpty(Cell cell) {
    drawCell(
        cell.getX(),
        cell.getY(),
        L' ',
        0
    );
}
