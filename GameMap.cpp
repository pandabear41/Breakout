
#include <iostream>
#include "GameMap.h"

using namespace std;

GameMap::GameMap(int flags) {
    this->flags = flags;
}

GameMap::~GameMap() {

}

void GameMap::tick() {

}

void GameMap::render(SDL_Surface* display) {
    //cout << this->bricks.size() << endl;
    for (unsigned int i=0; i < this->bricks.size(); i++) {
        this->bricks.at(i)->render(display);
    }
}

void GameMap::reset() {

}

void GameMap::generateNew() {
    int rows, columns, brickType, incX, incY, initX;
    SDL_Surface* brickImg;
//    cout << sImg << endl;
    if (flags & MAP_TYPE_LARGE) {
        brickImg = lImg;
        brickType = 2;
        columns = LMX;
        rows = LMY - 2;
        incX = 32;
        incY = 16;
        initX = 16;
    } else if (flags & MAP_TYPE_SMALL) {
        brickImg = sImg;
        brickType = 3;
        columns = SMX;
        rows = SMY - 5;
        incX = 16;
        incY = 8;
        initX = 8;
    } else {
        return;
    }

    int x = 0;
    int y = 22;
    cout << "After init" << endl;
    for (int i = 1; i <= rows; i++) {
        x = initX;
        for (int j = 1; j <= columns; j++) {
            Brick* brick = new Brick(brickImg, incX, incY);
            brick->x = x;
            brick->y = y;
            brick->brickType = rand() % 10;
            brick->brickFlag = brickType;
            bricks.push_back(brick);
            x += incX;
        }
        y += incY;
    }
    cout << "After everything" << endl;
 }

void GameMap::loadMap(const string file) {

}

void GameMap::collidesWith(Ball* item) {
//    cout << this->bricks.size() << endl;
    for (unsigned int i=0; i < this->bricks.size(); i++) {
        Brick* brick = this->bricks.at(i);
        if (!brick->hidden) {
            ColliderData hitData;
            bool hit = brick->circle2Rectangle(item->x, item->y, brick, &hitData);
            if (hit) {
                //item->stop = true;
                brick->hidden = true;

                //ColliderData hitNoth;
                //while (brick->circle2Rectangle(item->x, item->y, brick, &hitNoth)) {
                //    item->y += 1.4 * item->direction.get_y();
                //    item->x -= 1.4 * item->direction.get_x();
                //}
                switch(hitData.config) {
                    /** Collision with a corner: it is a point 2 point collision
                    * so use the impact vector. */
                    case 0:
                    case 2:
                    case 4:
                    case 6:
                        item->bounceX();
                        item->bounceY();
                        return;
                    /** Collision with an edge: it is point 2 line collision
                    * so the adjustement vector depends only on the
                    * line verticality. */
                    case 1:
                    case 5:
                        item->bounceY();
                        return;

                    case 3:
                    case 7:
                        item->bounceX();
                        return;

                    default:
                        return;
                        break;
                }
            }
        }
    }
}
