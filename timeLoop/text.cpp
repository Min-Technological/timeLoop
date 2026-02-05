#pragma once
#include "Text.h"

Text::Text(SDL_Renderer* r, float& scale, float& depth) :
renderer(r, 0, 0, 30, 30, scale, depth) {
	TTF_Init();
}

void Text::set_font(std::string fontName) {
	if (fontSet) {
		TTF_CloseFont(font);
		font = nullptr;
	}
	std::string fontLocation = fontName + ".ttf";
	font = TTF_OpenFont(fontLocation.c_str(), 30.0f);

	if (font == NULL) {
		std::cout << "COULD NOT OPEN FONT! : " << SDL_GetError() << "\n";
	}
	
}

void Text::load_text(std::string text, SDL_Color colour) {

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), 0, colour);

	if (textSurface == NULL) {
		std::cout << "Unable to render text surface! SDL_ttf Error: " << SDL_GetError() << "\n";
	}
	else {
		renderer.load_textbox(textSurface);
		SDL_DestroySurface(textSurface);
	}

}

void Text::render_text(float x, float y) {
	renderer.render_textbox(x, y);
}

void Text::destroy() {
	TTF_Quit();
}
