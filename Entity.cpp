#include "Entity.h"

using namespace std;

Entity::Entity() {
	entitySurf = NULL;

	x = 0;
	y = 0;

	width = 0;
	height = 0;

	type = ENTITY_TYPE_GENERIC;
	flags = ENTITY_FLAG_NONE;

	speedX = 0;
	speedY = 0;

	accelX = 0;
	accelY = 0;

	maxSpeedX = 5;
	maxSpeedY = 5;

	colX = 0;
	colY = 0;

	colWidth = 0;
	colHeight = 0;

	//animControl = new Animation();
}

Entity::~Entity() {
}

bool Entity::load(const string file, int width, int height, int maxFrames) {
	if((entitySurf = Draw::loadBMP(file.c_str())) == NULL) {
		return false;
	}

	//Draw::setTransparent(entitySurf, 255, 0, 255);

	this->width = width;
	this->height = height;

	animControl.maxFrames = maxFrames;

    return true;
}

void Entity::tick() {

}

void Entity::render(SDL_Surface* display) {

}

void Entity::cleanup() {
    if(entitySurf) {
        SDL_FreeSurface(entitySurf);
    }

    entitySurf = NULL;
}

void Entity::animate() {
	animControl.onTick();
}

void Entity::collision(Entity* entity) {
}

void Entity::move(float moveX, float moveY) {
	if(moveX == 0 && moveY == 0) return;

	x += moveX;
	y += moveY;
}

void Entity::stopMove() {
	speedX = 0;
	accelX = 0;
	speedY = 0;
	accelY = 0;
}

bool Entity::collides(int oX, int oY, int oW, int oH) {
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

	int tX = (int)x + colX;
	int tY = (int)y + colY;

    left1 = tX;
    left2 = oX;

    right1 = left1 + width - 1 - colWidth;
    right2 = oX + oW - 1;

    top1 = tY;
    top2 = oY;

    bottom1 = top1 + height - 1 - colHeight;
    bottom2 = oY + oH - 1;


    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;

    if (right1 < left2) return false;
    if (left1 > right2) return false;

    return true;
}

