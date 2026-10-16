#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <windows.h>
#include "Snake.h"
#include "Renderer.h"
#include "Rand.h"

template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

const int LEFT_X = 0;
const int RIGHT_X = 119;
const int TOP_Y = 0;
const int BOTTOM_Y = 29;

const int tick = 10; //Time between two updates, ms

int snakeCount;
int snakeSpeedMs;
int snakeSize;
bool epileptionMode;

Renderer renderer;
std::queue<Cell> renderQueue;

//Checks the input and returns game run flag
bool checkInput(int argc, char* argv[]) {

    auto checkInputElement = overloaded {
        [argv](int inputNumber, int lowerLimit, int upperLimit, std::string exceptionMessage) {
            int input;
            try { input = std::stoi(argv[inputNumber]); } 
            catch (const std::invalid_argument& e) { throw std::invalid_argument("Char instead of number"); }
            if (input < lowerLimit || input > upperLimit) { throw std::invalid_argument(exceptionMessage); }
            return input;
        },
        
        [argv](int inputNumber, std::string exceptionMessage) {
            if(std::strcmp(argv[inputNumber], "Y") != 0 && std::strcmp(argv[inputNumber], "N") != 0) { throw std::invalid_argument(exceptionMessage); }
            if(std::strcmp(argv[inputNumber], "Y") == 0) { return true; }
            return false;
        },

        [](int lowerLimit, int upperLimit, std::string exceptionMessage) {
            int input;
            if(!(std::cin >> input)) { throw std::invalid_argument("Char instead of number"); }
            if (input < lowerLimit || input > upperLimit) { throw std::invalid_argument(exceptionMessage); }
            return input;
        },
        
        [](std::string exceptionMessage) {
            std::string input;
            std::cin >> input;
            if(input != "Y" && input != "N") { throw std::invalid_argument("Invalid epileption mode"); }
            if(input == "Y") { return true; }
            return false;
        }
    };

    if(argc > 1) {
        if(std::strcmp(argv[1], "--help") == 0 || std::strcmp(argv[1], "/?") == 0) {
            std::cout << "Snake speed (1-30)" << std::endl;
            std::cout << "Snake size (1-30)" << std::endl;
            std::cout << "Epileption mode (Y/N)" << std::endl;

            return false;
        } else {
            try {
                if(argc != 5) { throw std::invalid_argument("Invalid number of arguments"); }
                snakeCount = checkInputElement(1, 1, 30, "Count out of range");
                snakeSpeedMs = 1000 / checkInputElement(2, 1, 30, "Speed out of range");
                snakeSize = checkInputElement(3, 1, 30, "Size out of range");
                epileptionMode = checkInputElement(4, "Invalid epileption mode");
            } catch (const std::invalid_argument& e) {
                std::cout << "Invalid input: " << e.what() << std::endl;
                return false;
            }
        }
    } else {
        try {
            std::cout << "Snake count (1-30): ";
            snakeCount = checkInputElement(1, 30, "Count out of range");

            std::cout << "Snake speed (1-30): ";
            snakeSpeedMs = 1000 / checkInputElement(1, 30, "Speed out of range");

            std::cout << "Snake size (1-30): ";
            snakeSize = checkInputElement(1, 30, "Size out of range");

            std::cout << "Epileption mode (Y/N): ";
            epileptionMode = checkInputElement("Invalid epileption mode");

        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input: " << e.what() << std::endl;
            return false;
        }
        
    }
    return true;
}

//Updates all snakes' positions and renders them every 'tick' ms
void updateAllSnakes(std::vector<Snake>& snakes) {
    for(Snake& snake : snakes) {
        if(GetTickCount64() - snake.getLastMoveTimes() >= (ULONGLONG)snake.getSpeed()) {
            snake.moveLeft(renderQueue);
        }
    }

    while(renderQueue.size() > 0) {
        renderer.drawCell(renderQueue.front());
        renderQueue.pop();
    }
}

//Runs the game loop
void run(bool running) {
    if(!running) return;

    system("cls");

    std::vector<int> spawnDellays(snakeCount);
    for(int& i : spawnDellays) {
        i = Rand::getRandInt(0, 1000);
    }
    std::sort(spawnDellays.begin(), spawnDellays.end(), std::greater<int>());

    std::vector<Snake> snakes;
    bool allSnakesSpawnedFlag = false;
    ULONGLONG start = GetTickCount64();
    
    while(true) {
        if(!allSnakesSpawnedFlag && GetTickCount64() - start >= spawnDellays.back()) {
            snakes.push_back(Snake(snakeSpeedMs, snakeSize, epileptionMode));
            snakes.back().addHead(RIGHT_X, Rand::getRandInt(TOP_Y + 1, BOTTOM_Y - 1), renderQueue);
            spawnDellays.pop_back();

            if(spawnDellays.size() == 0) {
                allSnakesSpawnedFlag = true;
            }
        }

        updateAllSnakes(snakes);
        Sleep(tick);
    }
}

int main(int argc, char* argv[]) {
    run(checkInput(argc, argv));
}
