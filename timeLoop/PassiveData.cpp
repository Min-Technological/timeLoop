#include "PassiveData.h"

#include <SDL3/SDL.h>

PassiveData::PassiveData() :
	x(920), y(600), xVelocity(0), yVelocity(0), xCamera(0), yCamera(0) {}

void PassiveData::set_player_postition(float x, float y, float xVelocity, float yVelocity) {
	this->x = x;
	this->y = y;

	this->xVelocity = xVelocity;
	this->yVelocity = yVelocity;
}

void PassiveData::set_camera_position(float xCamera, float yCamera) {
	this->xCamera = xCamera;
	this->yCamera = yCamera;
}




std::array<float, 4> PassiveData::get_player_position() {
	return { x, y, xVelocity, yVelocity };
}
std::array<float, 2> PassiveData::get_camera_position() {
	return { xCamera, yCamera };
}
