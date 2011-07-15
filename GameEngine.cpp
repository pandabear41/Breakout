#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine(const int width, const int height, const bool fullscreen) {
    Uint32 flags;

    if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
        printf("Can't init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    if (fullscreen) {
        flags = SDL_SWSURFACE | SDL_FULLSCREEN;
    } else {
        flags = SDL_SWSURFACE;
    }

    this->screen = SDL_SetVideoMode(width, height, 32, flags);
    if (NULL == screen) {
        printf("Can't set video mode: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_EnableUNICODE(1);

    // Initiate font
    TTF_Init();

    int imgFlags=IMG_INIT_JPG|IMG_INIT_PNG;
    IMG_Init(imgFlags);

    this->state = NULL;
    this->tickInterval = 20;
    this->renderInterval = 20;
}

GameEngine::~GameEngine() {
    delete this->state;
    this->state = NULL;

    atexit(TTF_Quit);
    SDL_Quit();
}


void GameEngine::setState(AbstractGameState* state) {
    delete this->state;
    this->state = state;
}

/**
* TickInterval is 1000 / tick = FPS (frame per second)
*/
void GameEngine::setTickInterval(int interval) {
    this->tickInterval = interval;
}

void GameEngine::setRenderInterval(int interval) {
    this->renderInterval = interval;
}

/**
* Run the game
*/
void GameEngine::loop() {
    SDL_Event event;
    Uint32 nextTick;
    Uint32 nextRender;

    if (NULL == this->state) {
        return;
    }

    this->done = false;
    nextRender = SDL_GetTicks() + this->renderInterval;
    while (!this->done) {
        nextTick = SDL_GetTicks() + this->tickInterval;

        // Listen to key or mouse events
        while (SDL_PollEvent(&event)) {
            this->state->event = event;

            Uint8 *keystates = SDL_GetKeyState(NULL);

            // Increase game speed while pressing space and moving mouse.
            if (keystates[SDLK_SPACE]) {
                this->state->clockTick();
            }

            switch (event.type) {
                case SDL_QUIT:
                    this->done = true;
                    break;
                case SDL_KEYDOWN:
                    this->state->keyPressed(event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    this->state->keyReleased(event.key.keysym.sym);
                    break;
        }
    }

    // Game tick
    this->state->clockTick();

    if (!(SDL_GetTicks() < nextRender)) {
        nextRender = SDL_GetTicks() + this->renderInterval;
        // Redraw screen
        this->state->draw(screen);
        // print out to screen
        SDL_Flip(screen);
    }


    // if state have set a state inside state, change state.
    if (NULL != this->state->state) {
        this->setState(this->state->state);
    }

    if (this->state->done) {
        this->done = true;
    }

    // To correct deley time.
    if (SDL_GetTicks() < nextTick) {
        SDL_Delay(nextTick - SDL_GetTicks());
    }
}

}
