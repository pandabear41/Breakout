#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include "AbstractGameState.h"
#include "GameEngine.h"
#include "Draw.h"


class GameState: public AbstractGameState {
public:
	GameState();
	virtual ~GameState();

	void draw(SDL_Surface* surface);
	void clockTick();
	void keyPressed(SDLKey key);

private:
    int tickCount;
    int score;
    int lives;
    SDL_Surface* balls;
;
};


#endif // GAMESTATE_H_INCLUDED
