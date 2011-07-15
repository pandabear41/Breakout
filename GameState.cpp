#include "GameState.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

SDL_Surface* bricksResource;

GameState::GameState() {
    this->tickCount = 0;
    this->score = 0;

    // Set and load the image for the balls.
    this->lives = 3;
    this->balls = Draw::loadBMP("data/balls.bmp");
    Draw::setTransparent(this->balls, 0,0,0);

    this->ball = new Ball();

    this->paddle = new Paddle();
    this->ball->paddle = this->paddle;

    this->bricksResourceS = Draw::loadBMP("data/bricks_small.bmp");
    this->bricksResourceL = Draw::loadBMP("data/bricks.bmp");

    this->gMap = new GameMap(MAP_TYPE_LARGE);
    this->gMap->lImg = this->bricksResourceL;
    this->gMap->sImg = this->bricksResourceS;
    this->gMap->generateNew();
}

GameState::~GameState() {
    SDL_FreeSurface(this->balls);
    this->balls = NULL;
}

void GameState::clockTick() {

    tickCount++;
    this->score++;
    // update Paddle
    this->paddle->tick();
    this->gMap->tick();
    // Update ball
    if (this->ball->dead == false && this->ball->launched == true ) {
        this->ball->tick();
        this->gMap->collidesWith(this->ball);
    } else if (this->ball->dead == true) {
        this->ball->dead = false;
        this->ball->launched = false;
        this->lives--;
        if (this->lives < 0) {
            // Gameover.
        }
        this->ball->cleanup();
    } else if (this->ball->launched == false) {
        this->ball->x = this->paddle->x + ((this->paddle->width / 2) - (this->ball->width / 2));
        this->ball->y = this->paddle->y - this->ball->height - 1;
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

    this->gMap->render(surface);
    this->ball->render(surface);
    this->paddle->render(surface);

    // Draw Score.
    char buffer[15];
    sprintf(buffer,"%d",this->score);
    Draw::drawText(surface, buffer, color, "font/SFDIGIT.TTF", 7, 3, 25);

    int xB=320-7-12; //Room for wall and balls.
    for (int i = 1; i <= this->lives; i++) {
        Draw::drawSurface(surface, this->balls, xB, 3, 0, 0, 12, 12);
        xB-=14;
    }

}

void GameState::keyPressed(SDLKey key) {
    switch (key) {
        case SDLK_g:
            if (this->ball->launched == false) {
                this->ball->cleanup();
                this->ball->launched = true;
            }
            break;
        case SDLK_LEFT:
            this->paddle->keyDown(1);
            break;
        case SDLK_RIGHT:
            this->paddle->keyDown(2);
            break;
        default:
            break;
    }

}

void GameState::keyReleased(SDLKey key) {
    switch (key) {
        case SDLK_LEFT:
            this->paddle->keyUp(1);
            break;
        case SDLK_RIGHT:
            this->paddle->keyUp(2);
            break;
        default:
            this->ball->stop = false;
            break;
    }
}
