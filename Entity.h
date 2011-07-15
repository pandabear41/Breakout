#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <vector>
#include <string>
#include "Animation.h"
#include "Camera.h"
#include "Draw.h"
#include "Defines.h"

struct ColliderData {
  int config;
  Vector2d impact_vector;
  //Entity *from_object;
};

enum {
	ENTITY_TYPE_GENERIC = 0,

	ENTITY_TYPE_PLAYER
};

enum {
	ENTITY_FLAG_NONE 	= 0,

	ENTITY_FLAG_GRAVITY	= 0x00000001,
	ENTITY_FLAG_GHOST	= 0x00000002,
	ENTITY_FLAG_MAPONLY	= 0x00000004
};

class Entity {
	public:
		float x;
		float y;
		int	width;
		int	height;

		int	type;
		bool dead;
		int	flags;
		float maxSpeedX;
		float maxSpeedY;

		Entity();
		virtual ~Entity();
		virtual bool load(const std::string file, int width, int height, int maxFrames);
		virtual void tick();
		virtual void render(SDL_Surface* display);
		virtual void cleanup();
		virtual void animate();
		virtual bool collision(Entity* entity);

		void move(float moveX, float moveY);

		void stopMove();
		bool collides(Entity* object);
		bool collides(int oX, int oY, int oW, int oH);
		bool circle2Rectangle(int x, int y, Entity* entity, ColliderData* data);
	protected:
		Animation animControl;
		SDL_Surface* entitySurf;
		float speedX;
		float speedY;

		float accelX;
		float accelY;

		int	colX;
		int	colY;
		int	colWidth;
		int	colHeight;
};

#endif // ENTITY_H_INCLUDED
