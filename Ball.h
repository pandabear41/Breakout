#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED


typedef struct SDL_Point {
  int x;
  int y;
} SDL_Point;

#include "Entity.h"

struct ColliderData {
  int config;
  int x,y;
  Entity *from_object;
};


class Ball: public Entity {
    public:
        bool launched;
        double speed;
        double direction;
        Ball();
        ~Ball();
        void tick();
		void render(SDL_Surface* display);
		void cleanup();
		void collision(Entity* entity);
        bool circle2Rectangle(Entity* entity, ColliderData* data);
    private:
};

#endif // BALL_H_INCLUDED
