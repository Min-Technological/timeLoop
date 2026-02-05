#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "Renderer.h"


#ifndef TEXT
#define TEXT

class Text {
public:
	Text(SDL_Renderer* r, float& scale, float& depth);

	void set_font(std::string fontName);

	void load_text(std::string text, SDL_Color colour);
	void render_text(float x, float y);

	void destroy();

private:
	bool fontSet = false;
	TTF_Font* font = nullptr;

	SDL_Texture* textBox = nullptr;

	Renderer renderer;




};


#endif