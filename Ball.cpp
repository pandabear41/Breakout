

#include "Ball.h"
#include <cmath>
#include <iostream>
#include <algorithm>

#include <algorithm>



using namespace std;

const float BALL_MAX_SPD = 7;
const float BALL_MIN_SPD = 5;

Ball::Ball() {
    load("data/balls.bmp", 12, 12, 5);
    Draw::setTransparent(this->entitySurf, 0, 0, 0);
    this->launched = false;
    this->dead = false;
    this->stop=false;

    cleanup();
}

Ball::~Ball() {
    SDL_FreeSurface(this->entitySurf);
}

void Ball::bounceX() {
    //dX = -randF(dX * 0.9, dX * 1.1);
    dX = -dX;
	//if (rand() % 100 < 10)
	//	dX = randSS(randI(BALL_MIN_SPD , BALL_MAX_SPD ));
}


void Ball::bounceY() {
    dY = -randF(dY * 0.9, dY * 1.1);
}

float Ball::randSS(float num) {
       if (rand() % 100 < 50)
        {
                return num;
        }
        return -num;
}

float Ball::randF(float min, float max) {
    cout << min << "...." << max << endl;
    float tmp = (static_cast<float> (this->randI( (int)(min * 1000.0),(int)(max * 1000.0)))) / 1000.0;
    cout << tmp << "rf" << endl;
    return tmp;
}

float Ball::randI(int min, int max) {


    if (min - max == 0)
    {
        return 0 + min; // avoid zero division
    }

    if (min > max)
    {
        int tmp;
        tmp = min;
        min = max;
        max = tmp;
    }

    int tmp =  ( rand() % (max - min) ) + min;
    return tmp;
}


void Ball::tick() {

    dY = min(dY, (float) (this->paddle->height*0.5));
    dY = max(dY, (float) (-this->paddle->height*0.5));

    dX = min(dX, (float) (this->paddle->width*0.15));
    dX = max(dX, (float) (-this->paddle->width*0.15));

    if (this->dX > BALL_MAX_SPD) {
        dX *=.95;
    } //else if (this->dX < BALL_MIN_SPD) {
    //    dX *=1.05;
    //}

    if (this->dY > BALL_MAX_SPD) {
        dY *=.95;
    } else if (this->dY < BALL_MIN_SPD) {
        dY *= 1.05;
    }

    int newX = this->x + dX;
    int newY = this->y + dY;


    ColliderData hitarea;
    if (this->circle2Rectangle(newX, newY,this->paddle, &hitarea) && dY > 0) {


        switch(hitarea.config) {
                /** Collision with a corner: it is a point 2 point collision
                * so use the impact vector. */
                case 0:
                case 2:
                case 4:
                case 6:
                    this->bounceX();
                    this->bounceY();
                    break;
                /** Collision with an edge: it is point 2 line collision
                * so the adjustement vector depends only on the
                * line verticality. */
                case 1:
                    this->bounceY();
                    this->dX = -((this->paddle->x+(this->paddle->width/2)) - (this->x+6))/4 + this->dX/2;
                    break;

                case 3:
                case 7:
                    this->bounceX();
                    this->dX *= 1.5;
                    this->x += dX;
                    return;
                    break;

                case 5:
                    this->y += dY;
                default:
                    return;
                    break;
        }
        //forces.insert(new Vector2d(mod, -2*direction.get_y()));
        // Not needed for now.
        //while (this->circle2Rectangle(newX, newY,this->paddle, &hitarea)) {
        //   newY += 1.3 * direction.get_y();
        //   newX -= 1.3 * direction.get_x();
        //}

        //newX = this->x;
        //this->stop = true;
    }
    if (!this->stop) {
        if(newX > 303) {
            bounceX();
            this->x = 303;


        } else if (newX < 5) {
            bounceX();
            this->x = 5;

        } else {
            this->x = newX;
        }

        if (newY < 0) {
            bounceY();
            this->y = 0;
        } else {
            this->y = newY;
        }
    }

    if (newY > 240) {
        this->dead = true;
    }
    //this->updateDirection();

}

void Ball::render(SDL_Surface* display) {
    Draw::drawSurface(display, this->entitySurf, this->x, this->y, 12, 0, 12, 12);
}

void Ball::cleanup() {
    dY = -randF(BALL_MIN_SPD, BALL_MAX_SPD );
    dX = randF(BALL_MIN_SPD, BALL_MAX_SPD);
}

bool Ball::collision(Entity* entity) {
    return false;
}





