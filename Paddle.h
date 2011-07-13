#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include "Entity.h"

class Paddle: public Entity {
    public:
        Paddle();
        ~Paddle();
        void tick();
        void keyDown(int key);
        void keyUp(int key);
		void render(SDL_Surface* display);
		void cleanup();
		void collision(Entity* entity);
    private:
};

#endif // PADDLE_H_INCLUDED
