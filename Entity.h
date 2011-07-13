#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <vector>
#include <string>
#include "Animation.h"
#include "Camera.h"
#include "Draw.h"

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
		virtual void collision(Entity* entity);

		void move(float moveX, float moveY);

		void stopMove();
		bool collides(int oX, int oY, int oW, int oH);
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
