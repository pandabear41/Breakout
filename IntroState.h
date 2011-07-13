#ifndef INTROSTATE_H_INCLUDED
#define INTROSTATE_H_INCLUDED

#include "AbstractGameState.h"
#include "GameEngine.h"
#include "Draw.h"

class IntroState: public AbstractGameState {
public:
	IntroState();
	virtual ~IntroState();

	void draw(SDL_Surface* surface);
	void clockTick();
	void keyPressed(SDLKey key);

private:
    int textAlpha;
    bool forward;
    int tickCount;
};

#endif // INTROSTATE_H_INCLUDED
