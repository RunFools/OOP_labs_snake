#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cstdlib>
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

int LEFT_X = 0;
int RIGHT_X = 119;
int TOP_Y = 0;
int BOTTOM_Y = 29;

int snakeCount = 1;
int snakeSpeed = 30;
int snakeSize = 30;
bool epileptionMode = false;

Renderer renderer;

//Sleep that depends on the snake speed
void localSleep() {
    Sleep(1000/snakeSpeed);
}

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
                snakeSpeed = checkInputElement(2, 1, 30, "Speed out of range");
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
            snakeSpeed = checkInputElement(1, 30, "Speed out of range");

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

//Creates a game loop for a single snake
void runLocalGameLoop(Snake snake) {
    snake.addHead(RIGHT_X, Rand::getRandInt(TOP_Y + 1, BOTTOM_Y - 1));

    while(snake.getSize() < snakeSize) {
        renderer.drawSnake(snake.getHead());

        localSleep();

        snake.moveLeft();
    }
    snake.setLongEnough(true);

    while(snake.getSize() > 0) {
        renderer.drawSnake(snake.getHead());

        localSleep();

        renderer.drawEmpty(snake.getTail());
        snake.moveLeft(); 
    }
    snake.setLongEnough(false);
}

//Ties all the game loops into one
void runGlobalGameLoop(bool running) {
    while(running) {
        system("cls");

        runLocalGameLoop(Snake(epileptionMode));
    }
}


int main(int argc, char* argv[]) {
    runGlobalGameLoop(checkInput(argc, argv));
}