
#include <time.h>
#include "GameEngine.h"
#include "IntroState.h"



using namespace std;

int main(int argc, char **argv) {
    // To get random number
    srand((unsigned) time(NULL));

    // Start game.
    GameEngine* engine = new GameEngine(320, 240, false);

    // Begin IntroState
    AbstractGameState* state = new IntroState();
    engine->setState(state);
    engine->setTickInterval(30);
    engine->setRenderInterval(30);

    // Keep alive
    engine->loop();

    delete engine;
    engine = NULL;

    return 0;
}

