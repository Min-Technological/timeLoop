#pragma once
#pragma once
#ifndef PASSIVEDATA
#define PASSIVEDATA

#include <SDL3/SDL.h>

class PassiveData {
public:
	PassiveData();

	Uint64 return_frame() const;

	float x, y;
	float xVelocity, yVelocity;
private:
	Uint64 frameSnap;
};



#endif
