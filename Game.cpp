#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cstdlib>
#include <windows.h>
#include "Snake.h"
#include "Renderer.h"
#include "Rand.h"


int LEFT_X = 0;
int RIGHT_X = 119;
int TOP_Y = 0;
int BOTTOM_Y = 29;

int snakeSize = 30;
int snakeSpeed = 30;


void localSleep() {
    Sleep(1000/snakeSpeed);
}


int main(int argc, char* argv[]) {

    Renderer renderer;
    Snake snake = Snake();

    bool running = true;

    if(argc > 1) {
        if(std::strcmp(argv[1], "--help") == 0 || std::strcmp(argv[1], "/?") == 0) {
            std::cout << "Snake speed (1-30)" << std::endl;
            std::cout << "Snake size (1-30)" << std::endl;
            std::cout << "Epileption mode (Y/N)" << std::endl;

            running = false;
        } else {
            try {
                if(argc != 4) {
                    throw std::invalid_argument("Invalid number of arguments");
                }

                int speed = std::stoi(std::string(argv[1]));
                if (speed < 1 || speed > 30) { 
                    throw std::invalid_argument("Speed out of range");
                }
                snakeSpeed = speed;

                int size = std::stoi(std::string(argv[2]));
                if (size < 1 || size > 30) { 
                    throw std::invalid_argument("Size out of range");
                }
                snakeSize = size;

                if(std::strcmp(argv[3], "Y") != 0 && std::strcmp(argv[3], "N") != 0) {
                    throw std::invalid_argument("Invalid epileption mode");
                }
                if(std::strcmp(argv[3], "Y") == 0) {
                    snake.setEpileptionMode(true);
                }
            } catch (const std::invalid_argument& e) {
                std::cout << "Invalid input: " << e.what() << std::endl;
                running = false;
            } catch (const std::logic_error& e) {
                std::cout << "Invalid input: Unknown source" << std::endl;
                running = false;
            }
        }
    } else {
        try {
            int speed;
            std::cout << "Snake speed (1-30): ";
            if(!(std::cin >> speed)) {
                throw std::invalid_argument("Char instead of number");
            } else {
                if (speed < 1 || speed > 30) { 
                    throw std::invalid_argument("Speed out of range");
                }
                snakeSpeed = speed;
            }

            int size;
            std::cout << "Snake size (1-30): ";
            if(!(std::cin >> size)) {
                throw std::invalid_argument("Char instead of number");
            } else {
                if (size < 1 || size > 30) { 
                    throw std::invalid_argument("Size out of range");
                }
                snakeSize = size;
            }

            std::string epileptionMode;
            std::cout << "Epileption mode (Y/N): ";
            std::cin >> epileptionMode;
            if(epileptionMode != "Y" && epileptionMode != "N") {
                throw std::invalid_argument("Invalid epileption mode");
            }
            if(epileptionMode == "Y") {
                snake.setEpileptionMode(true);
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input: " << e.what() << std::endl;
            running = false;
        }
        
    }

    while(running) {
        system("cls");

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

    
}