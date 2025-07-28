#pragma once
#pragma once
#ifndef PASSIVEDATA
#define PASSIVEDATA

#include <SDL3/SDL.h>

class PassiveData {
public:
	PassiveData();

	void provide_frame(Uint64 frame);
	Uint64 return_frame() const;

	float x, y;
	float xVelocity, yVelocity;
private:
	Uint64 frameSnap;
};



#endif
