#pragma once
#ifndef BACKGROUND
#define BACKGROUND

#include <SDL3/SDL.h>

class Background {
public:
	Background(SDL_Renderer* renderer);

	void handle_event(bool fullscreenState);

	void update(int screenW, int screenH);

	void render();
private:
	SDL_FRect t = { 0, 0, 960, 540 }; // Texture
	SDL_Renderer* r; // Renderer
};


#endif
