#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "Entity.h"
#include "Vector2d.h"
#include "Paddle.h"
#include <set>
#include <stack>
#include <algorithm>
#include <cmath>

class Ball: public Entity {
    public:
        bool stop;
        bool launched;
        Paddle* paddle;
        float dX;
		float dY;
		float lastY;
        Ball();
        ~Ball();
        void tick();
		void render(SDL_Surface* display);
		void cleanup();
		bool collision(Entity* entity);


        void bounceX();
        void bounceY();

    private:
        float randF(float min, float max);
        float randI(int min, int max);
        float randSS(float num);

};

#endif // BALL_H_INCLUDED
