
#include <iostream>
#include "IntroState.h"
#include "GameState.h"

using namespace std;

IntroState::IntroState() {
    this->textAlpha=255;
    this->tickCount=0;
    this->forward = false;
}

IntroState::~IntroState() {

}

void IntroState::clockTick() {
    tickCount++;
    if (forward) {
        this->textAlpha += 10;
    } else {
        this->textAlpha -= 10;
    }
    if (this->textAlpha >= 255) {
        this->textAlpha=254;
        this->forward = false;
    } else if (this->textAlpha <= 0) {
        this->textAlpha=0;
        this->forward = true;
    }
    this->reDraw = true;
}

void IntroState::draw(SDL_Surface* surface) {

	// To avoid redrawing every tick when nothing have actually changed.
	if (!this->reDraw) {
		return;
	} else {
		this->reDraw = false;
	}

    SDL_FillRect(surface,NULL, 0x000000);

	// white
	SDL_Color color = { 255, 255, 255, 0 };

	// Print out menu
	Draw::drawText(surface, "Breakout", color, 160-75, 15, 40, 255);
    Draw::drawText(surface, "Press Any Button", color, 160-100, 160, 28, this->textAlpha);
    Draw::drawText(surface, "To Start", color, 160-50, 190, 28, this->textAlpha);

}

void IntroState::keyPressed(SDLKey key) {
    this->state = new GameState();
}
