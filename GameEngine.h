#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#ifdef WIN32
    #include <SDL_image.h>
#else
    #include <SDL/SDL_image.h>
#endif

#include "AbstractGameState.h"

class GameEngine {

public:
    /**
    * Initiate SDL and GUI
    */
    GameEngine(const int width, const int height, const bool fullscreen);
    ~GameEngine();

    /**
    * Available states: IntroState, PlayState, GameOverState, EditMapState
    */
    void setState(AbstractGameState* state);
    /**
    * TickInterval is 1000 / tick = FPS (frame per second)
    */
    void setTickInterval(int interval);
    /**
    * Run the game
    */
    void loop();

private:
    AbstractGameState* state;
    SDL_Surface* screen;
    bool done;
    int tickInterval;
};

#endif // GAMEENGINE_H
