#include "AbstractGameState.h"

using namespace std;

AbstractGameState::AbstractGameState() {
    this->done = false;
    this->reDraw = true;
    this->state = NULL;
}

AbstractGameState::~AbstractGameState() {
    SDL_FreeSurface(this->background);
}

void AbstractGameState::clockTick() {
}

void AbstractGameState::draw(SDL_Surface* surface) {
}

void AbstractGameState::keyPressed(SDLKey key) {
}

void AbstractGameState::keyReleased(SDLKey key) {
}

/**
* Convert Int to String.
*/
const string AbstractGameState::intToString(const int number) {
    stringstream ss;
    string str;
    ss << number;
    ss >> str;
    return str;
}


