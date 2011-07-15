
#include "Paddle.h"
#include <iostream>

using namespace std;

Paddle::Paddle() {
    cout << "loaded" << endl;
    load("data/bat.bmp", 53, 10, 1);
    this->speed = 7;
    cleanup();
}

Paddle::~Paddle() {
    SDL_FreeSurface(this->entitySurf);
}

void Paddle::tick() {
    int newX = this->x;
    if (this->goingLeft) {
        newX = this->x - this->speed;
        if (newX < 5) {
            newX = 5;
        }
    } else if (this->goingRight) {
        newX = this->x + this->speed;
        if (newX > SWIDTH - this->width - 5) {
            newX = SWIDTH - this->width - 5;
        }
    }
    this->x = newX;
}

void Paddle::keyDown(int key) {
    if (key == 1) {
        this->goingLeft = true;
    } else if (key == 2) {
        this->goingRight = true;
    }
}

void Paddle::keyUp(int key) {
    if (key == 1) {
        this->goingLeft = false;
    } else if (key == 2) {
        this->goingRight = false;
    }
}

void Paddle::render(SDL_Surface* display) {
    Draw::drawSurface(display, this->entitySurf, this->x, this->y, 0, 0, 53, 10);
}

void Paddle::cleanup() {
    this->goingLeft = false;
    this->goingRight = false;
    this->x = SWIDTH/2 - 53;
    this->y = SHEIGHT - 15;
}

