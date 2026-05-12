#pragma once
#ifndef ENTRY
#define ENTRY

#include <SDL3/SDL.h>
#include "Renderer.h"
#include "Input.h"

class Entry {
public:
	Entry(SDL_Renderer* r, float& scale, float& depth, float x, float y);
	
	void set_texture(std::string textureName);

private:
	Renderer renderer;
};



#endif