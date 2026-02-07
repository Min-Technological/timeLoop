#pragma once
#include "Text.h"

Text::Text(SDL_Renderer* r, float& scale, float& depth) :
	renderer(r, 0, 0, 30, 30, scale, depth),
	scale(scale) {
	TTF_Init();
}

void Text::set_font(TTF_Font* presetFont) {
	font = presetFont;
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

void Text::new_position(float newX, float newY, float newW, float newH, float xOff, float yOff) {
	renderer.new_position(newX, newY, newW, newH, xOff, yOff);
}

void Text::render_text() {
	renderer.render_texture();
}

std::array<int, 2> Text::get_dimensions() {
	return renderer.texture_dimensions();
}

void Text::destroy() {
	TTF_Quit();
}
