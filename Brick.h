#ifndef BRICK_H_INCLUDED
#define BRICK_H_INCLUDED

#include "Entity.h"

enum {
	BRICK_FLAG_NONE 	= 0,
	BRICK_FLAG_LARGE    = 2, // With large you can do 9*11 of bricks.
	BRICK_FLAG_SMALL    = 3, // With small you can do 19*22 of bricks.
};

class Brick: public Entity {
    public:
        int brickFlag;
        int brickType;
        bool hidden;
        Brick(SDL_Surface* brickImg, int width, int height);
        ~Brick();
        void tick();
		void render(SDL_Surface* display);
		void cleanup();

		SDL_Surface* brickRes;
    private:
};

#endif // BRICK_H_INCLUDED
