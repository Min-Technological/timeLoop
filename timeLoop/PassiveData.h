#pragma once
#pragma once
#ifndef PASSIVEDATA
#define PASSIVEDATA

#include <SDL3/SDL.h>
#include <array>
#include "Enums.h"



class PassiveData {
public:
	PassiveData();

	// === Player Passive Helpers ===
	void set_player_postition(float x, float y, float xVelocity, float yVelocity);
	std::array<float, 4> get_player_position();

	void set_persona(Persona persona);
	Persona get_persona();



	// === Camera Passive Helpers ===
	void set_camera_position(float xCamera, float yCamera);
	std::array<float, 2> get_camera_position();




private:
	// === Player Passives ===
	float x, y;
	float xVelocity, yVelocity;
	Persona currentPersona = Persona::PROTAG;

	// === Camera Passives ===
	float xCamera, yCamera;
};



#endif
