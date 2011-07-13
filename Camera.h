#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <SDL.h>

enum {
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

class Camera {
	public:
		static Camera cameraControl;
		int targetMode;
		Camera();
		void onMove(int moveX, int moveY);
		int getX();
		int getY();
		void setPos(int x, int y);
		void setTarget(float* x, float* y);


	private:
		int x;
		int y;
		float* targetX;
		float* targetY;
};


#endif // CAMERA_H_INCLUDED