#include "PassiveData.h"

#include <SDL3/SDL.h>

PassiveData::PassiveData() :
	x(920), y(600), xVelocity(0), yVelocity(0), frameSnap(0) {}

void PassiveData::provide_frame(Uint64 frame) {
	frameSnap = frame;
}

Uint64 PassiveData::return_frame() const {
	return frameSnap;
}