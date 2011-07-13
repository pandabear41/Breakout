
#include <iostream>
#include "Ball.h"
#include <math.h>

using namespace std;

Ball::Ball() {
    load("data/balls.bmp", 12, 12, 5);
    Draw::setTransparent(this->entitySurf, 0, 0, 0);
    this->launched = true;
    this->dead = false;
    this->speed = 7;
    this->direction = random() * 2.*M_PI / (double)RAND_MAX;
    cleanup();
}

Ball::~Ball() {
    SDL_FreeSurface(this->entitySurf);
}

void Ball::tick() {
    int newX = this->x + this->speed * cos(this->direction);
    int newY = this->y - this->speed * sin(this->direction);

    if(newX < 5 || newX > 303) {
        this->direction = M_PI - this->direction;
        if (newX > 303) {
            this->direction += .2;
            this->x = 303;
        } else if (newX < 5) {
            this->direction -= .2;
            this->x = 5;
        }

    } else {
        this->x = newX;
    }

    if(newY < 0) {
        this->direction = -this->direction + .2;
        this->y = 0;
    } else {
        this->y = newY;
    }

    if (newY > 240) {
        this->dead = true;
    }
    // Protection for sideways.
    if (this->direction == 0 || this->direction == M_PI || this->direction == 2*M_PI) {
        cout << "Noooooooo" <<endl;
        this->direction = random() * 2.*M_PI / (double)RAND_MAX;
    }
}

void Ball::render(SDL_Surface* display) {
    Draw::drawSurface(display, this->entitySurf, this->x, this->y, 12, 0, 12, 12);
}

void Ball::cleanup() {
    x=250;
    y=25;
}

void Ball::collision(Entity* entity) {

}

bool Ball::circle2Rectangle(Entity* entity, ColliderData* data) {
    int radius = 6;
    int cx = this->x+radius;
    int cy = this->y+radius;
    int x1 = entity->x;
    int y1 = entity->y;
    int x2 = x1+entity->width;
    int y2 = y1+entity->height;
    int xmid = x2 - static_cast<int>((double)entity->width/2.);
    int ymid = y2 - static_cast<int>((double)entity->height/2.);
    int config = -1;

    // Check for edge collision
      if ((x1<=cx) && (cx<x2)) {
        if ((cy>=y1-radius) && (cy<ymid)) {//y1)) {
          config = 1;
        }
        else if ((cy<=y2+radius) && (cy>ymid)) {//y2)) {
          config = 5;
        }
      }
      else if ((y1<=cy) && (cy<y2)) {
        if ((cx>=x1-radius) && (cx<xmid)) {//x1)){
          config = 7;
        }
        else if ((cx<=x2+radius) && (cx>xmid)) {//x2)) {
          config = 3;
        }
      }
      // Check for corner collision
      if (config == -1) {
        SDL_Point corner = {-1,-1};
        int potential_config = -1;

        if (cx<x1) {
          if (cy<y1) {
            corner.x = x1;
            corner.y = y1;
            data->x = x1 - cx;
            data->y = y1 - cy;
            potential_config = 0;
          }
          else if (cy>y2) {
            corner.x = x1;
            corner.y = y2;
            data->x = x1 - cx;
            data->y = y2 - cy;
            potential_config = 6;
          }
        }
        else if (cx>x2) {
          if (cy<y1) {
            corner.x = x2;
            corner.y = y1;
            data->x = x2 - cx;
            data->y = y1 - cy;
            potential_config = 2;
          }
          else if (cy>y2) {
            corner.x = x2;
            corner.y = y2;
            data->x = x2 - cx;
            data->y = y2 - cy;
            potential_config = 4;
          }
        }
        if ((cx-corner.x)*(cx-corner.x) + (cy-corner.y)*(cy-corner.y)
              < radius*radius) {
              config = potential_config;
        }
      }
      data->config = config;
      return config != -1;


}
