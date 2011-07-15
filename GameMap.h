#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED


#include <vector>
#ifdef WIN32
    #include <SDL.h>
#else
    #include <SDL/SDL.h>
#endif
#include "Entity.h"
#include "Brick.h"
#include "Draw.h"
#include "Defines.h"
#include "Ball.h"


enum {
    MAP_TYPE_NONE = 0,

    MAP_TYPE_RANDOM = 1,
    MAP_TYPE_SMALL = 2,
    MAP_TYPE_LARGE = 4,
};

class GameMap {
    public:
        int flags;
        SDL_Surface* lImg;
        SDL_Surface* sImg;
        GameMap(int flags);
        ~GameMap();
        void tick();
        void render(SDL_Surface* display);
        void reset();
        void generateNew();
        void collidesWith(Ball* item);
        void loadMap(const string file);

    private:
        vector<Brick*> bricks;
};

#endif // MAP_H_INCLUDED
