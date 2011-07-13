#include "GameState.h"
#include <iostream>
#include <stdio.h>

using namespace std;

GameState::GameState() {
    this->tickCount = 0;
    this->score = 0;

    // Set and load the image for the balls.
    this->lives = 3;
    this->balls = Draw::loadBMP("data/balls.bmp");
    Draw::setTransparent(this->balls, 0,0,0);

    this->ball = new Ball();

}

GameState::~GameState() {
    SDL_FreeSurface(this->balls);
    this->balls = NULL;
}

void GameState::clockTick() {
    tickCount++;
    this->score++;
    if (this->ball->dead == false && this->ball->launched == true ) {
        this->ball->tick();
    } else if (this->ball->dead == true) {
        this->ball->dead = false;
        this->ball->launched = false;
        this->lives--;
        if (this->lives < 0) {
            // Gameover.
        }
        this->ball->cleanup();
    } else {

    }

    this->reDraw = true;
}

void GameState::draw(SDL_Surface* surface) {

	// To avoid redrawing every tick when nothing have actually changed.
	if (!this->reDraw) {
		return;
	} else {
		this->reDraw = false;
	}

    SDL_FillRect(surface,NULL, 0x000000);

	// white color
	SDL_Color color = { 255, 255, 255, 0 };

    // Draw Side Walls.
    Draw::filledRect(surface, 0, 0, 5, 240, 0xC0C0C0);
    Draw::filledRect(surface, 315, 0, 5, 240, 0xC0C0C0);

    // Draw Score.
    char buffer[15];
    sprintf(buffer,"%d",this->score);
    Draw::drawText(surface, buffer, color, "font/SFDIGIT.TTF", 7, 3, 25);

    int xB=320-7-12; //Room for wall and balls.
    for (int i = 1; i <= this->lives; i++) {
        Draw::drawSurface(surface, this->balls, xB, 3, 0, 0, 12, 12);
        xB-=14;
    }

    this->ball->render(surface);
}

void GameState::keyPressed(SDLKey key) {
    switch (key) {
        case SDLK_g:
            if (this->ball->launched == false) {
                this->ball->direction = random() * 2.*M_PI / (double)RAND_MAX;
                this->ball->launched = true;
            }
        default:
            break;
    }

}
