#include "Camera.h"

using namespace std;

Camera Camera::cameraControl;

Camera::Camera() {
	x = y = 0;

	targetX = targetY = NULL;

	targetMode = TARGET_MODE_NORMAL;
}

//==============================================================================
void Camera::onMove(int moveX, int moveY) {
	x += moveX;
	y += moveY;
}

//==============================================================================
int Camera::getX() {
	if(targetX != NULL) {
		if(targetMode == TARGET_MODE_CENTER) {
			return *targetX - (320 / 2);
		}

		return *targetX;
	}

	return x;
}

//------------------------------------------------------------------------------
int Camera::getY() {
	if(targetY != NULL) {
		if(targetMode == TARGET_MODE_CENTER) {
			return *targetY - (320 / 2);
		}

		return *targetY;
	}

	return y;
}

//==============================================================================
void Camera::setPos(int x, int y) {
	this->x = x;
	this->y = y;
}

//------------------------------------------------------------------------------
void Camera::setTarget(float* x, float* y) {
	targetX = x;
	targetY = y;
}
