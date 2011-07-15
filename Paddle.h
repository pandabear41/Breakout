#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include "Defines.h"
#include "Entity.h"

class Paddle: public Entity {
    public:
        bool goingLeft;
        bool goingRight;
        double speed;
        Paddle();
        ~Paddle();
        void tick();
        void keyDown(int key);
        void keyUp(int key);
		void render(SDL_Surface* display);
		void cleanup();
    private:
};

#endif // PADDLE_H_INCLUDED
