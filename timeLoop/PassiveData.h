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
	void set_persona(int persona);
	void set_camera_position(float xCamera, float yCamera);




	std::array<float, 4> get_player_position();
	int get_persona();
	std::array<float, 2> get_camera_position();

private:
	// === Player Passives ===
	float x, y;
	float xVelocity, yVelocity;
	int currentPersona = 0;

	// === Camera Passives ===
	float xCamera, yCamera;
};



#endif
