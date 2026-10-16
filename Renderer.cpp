#include "Renderer.h"
#include "Rand.h"

void Renderer::drawCell(Cell cell) {
    CHAR_INFO ci;
    ci.Char.UnicodeChar = cell.getChar();
    ci.Attributes = cell.getColor();

    COORD      size   = { 1, 1 };
    COORD      origin = { 0, 0 };
    SMALL_RECT region = { cell.getX(), cell.getY(), cell.getX(), cell.getY() };

    WriteConsoleOutputW(hOut, &ci, size, origin, &region);
}
