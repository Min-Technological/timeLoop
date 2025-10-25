#pragma once
#pragma once
#ifndef PASSIVEDATA
#define PASSIVEDATA

#include <SDL3/SDL.h>
#include <array>

class PassiveData {
public:
	PassiveData();

	void set_player_postition(float x, float y, float xVelocity, float yVelocity);
	void set_camera_position(float xCamera, float yCamera);



	std::array<float, 4> get_player_position();
	std::array<float, 2> get_camera_position();

private:
	float x, y;
	float xVelocity, yVelocity;

	float xCamera, yCamera;
};



#endif
