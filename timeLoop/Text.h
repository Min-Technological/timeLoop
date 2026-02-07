#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "Renderer.h"
#include <array>


#ifndef TEXT
#define TEXT

class Text {
public:
	Text(SDL_Renderer* r, float& scale, float& depth);

	void set_font(TTF_Font* font);

	void load_text(std::string text, SDL_Color colour);
	void new_position(float newX, float newY, float newW, float newH, float xOff, float yOff);
	void render_text();

	std::array<int, 2> get_dimensions();

	void destroy();

private:
	float& scale;

	TTF_Font* font = nullptr;

	SDL_Texture* textBox = nullptr;

	Renderer renderer;




};


#endif