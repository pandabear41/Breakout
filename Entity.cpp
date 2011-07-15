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
    dead = false;

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

bool Entity::collision(Entity* entity) {
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

bool Entity::collides(Entity* object) {
    return this->collides(object->x, object->y, object->width, object->height);
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


bool Entity::circle2Rectangle(int x, int y, Entity* entity, ColliderData* data) {
    int radius = 6;
      int cx = x+radius;
      int cy = y+radius;
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
            data->impact_vector.set(
              x1 - cx, y1 - cy
            );
            potential_config = 0;
          }
          else if (cy>y2) {
            corner.x = x1;
            corner.y = y2;
            data->impact_vector.set(
              x1 - cx, y2 - cy
            );
            potential_config = 6;
          }
        }
        else if (cx>x2) {
          if (cy<y1) {
            corner.x = x2;
            corner.y = y1;
            data->impact_vector.set(
              x2 - cx, y1 - cy
            );
            potential_config = 2;
          }
          else if (cy>y2) {
            corner.x = x2;
            corner.y = y2;
            data->impact_vector.set(
              x2 - cx, y2 - cy
            );
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


