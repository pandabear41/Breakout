
#include <iostream>
#include "Brick.h"

using namespace std;

Brick::Brick(SDL_Surface* brickImg, int width, int height){
    brickFlag = 0;
    brickType = 0;
    brickRes = brickImg;
    this->width = width;
    this->height = height;
    hidden = false;

}

Brick::~Brick(){

}

void Brick::tick() {
    //Bricks don't do anything.
}

void Brick::render(SDL_Surface* display) {
    if (!this->hidden && this->brickFlag != 0) {
        if (brickFlag == BRICK_FLAG_LARGE) {
            Draw::drawSurface(display, brickRes, this->x, this->y, 32 * brickType, 0, 32, 16);
        } else if (brickFlag == BRICK_FLAG_SMALL) {
            Draw::drawSurface(display, brickRes, this->x, this->y, 16 * brickType, 0, 16, 8);
        }
    }
}

void Brick::cleanup() {
    // Clean up the brick.
}
