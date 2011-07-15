#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include "AbstractGameState.h"
#include "GameEngine.h"
#include "Draw.h"
#include "Ball.h"
#include "Paddle.h"
#include "GameMap.h"



class GameState: public AbstractGameState {
public:
	GameState();
	virtual ~GameState();

	void draw(SDL_Surface* surface);
	void clockTick();
	void keyPressed(SDLKey key);
    void keyReleased(SDLKey key);
    SDL_Surface* bricksResourceS;
    SDL_Surface* bricksResourceL;
private:
    int tickCount;
    int score;
    int lives;
    SDL_Surface* balls;
    Ball* ball;
    Paddle* paddle;
    GameMap* gMap;
};


#endif // GAMESTATE_H_INCLUDED
