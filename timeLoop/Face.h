#pragma once
#ifndef FACE
#define FACE

#include <SDL3\SDL.h>
#include <array>
#include "Renderer.h"



class Face {
public:
	Face();

	void update(std::array<SDL_Vertex, 4> verticies);

	void render(Renderer* r);

	

private:
	SDL_Vertex tempVertex = { {0, 0}, {0xFF, 0xFF, 0xFF, 0xFF}, {0, 0} };

	std::array<SDL_Vertex, 3> topLeftTriangle;
	std::array<SDL_Vertex, 3> bottomRightTriangle;
};


#endif
