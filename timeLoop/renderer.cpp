#include "Renderer.h"

Renderer::Renderer(SDL_Renderer* r, float X, float Y, float W, float H, float& s) :
	renderer(r), viewport( { X, Y, W, H } ), scale(s) {
}



void Renderer::load_texture(const std::string &path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface) {
		std::cout << "UNABLE TO LOAD IMAGE! " << SDL_GetError() << std::endl;
		return;
	}

	texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (!texture) {
		std::cout << "UNABLE TO CREATE TEXTURE FROM: " << SDL_GetError() << std::endl;
	}
	else {
		SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	}



	SDL_DestroySurface(loadedSurface);
}

void Renderer::new_position(float newX, float newY, float newW, float newH, float xOff) {
	xOffset = xOff;
	viewport.x = (newX -  xOffset) * scale;
	viewport.y = newY * scale;
	viewport.w = newW * scale;
	viewport.h = newH * scale;
}

void Renderer::render_colour(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
	SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
	SDL_RenderFillRect(renderer, &viewport);
}
void Renderer::render_texture() {
	SDL_RenderTexture(renderer, texture, NULL, &viewport);
}
void Renderer::render_sprite(float x, float y, float w, float h) {
	SDL_FRect sprite = { x, y, w, h };

	SDL_RenderTexture(renderer, texture, &sprite, &viewport);
}
void Renderer::render_hitbox(float xa, float ya, float xb, float yb, Uint8 green) {

	float width = xb - xa;
	float height = yb - ya;
	SDL_FRect bounding = {
		(xa - xOffset) * scale,
		ya * scale,
		width * scale,
		height * scale
	};

	SDL_SetRenderDrawColor(renderer, 255, green, 0, 255);
	SDL_RenderRect(renderer, &bounding);
}
void Renderer::render_clickbox(float x, float y, float w, float h, Uint8 green) {
	SDL_FRect bounding = {
		x * scale,
		y * scale,
		w * scale,
		h * scale
	};

	std::cout << "RENDERING! at scale: " << scale << "\n";
	SDL_SetRenderDrawColor(renderer, 0, green, 255, 255);
	SDL_RenderRect(renderer, &bounding);
}

bool Renderer::test_frame(std::vector<float> camera) const {
	if (viewport.x > -viewport.w && viewport.x < camera[0]) {
		if (viewport.y > -viewport.h && viewport.y < camera[1]) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void Renderer::destroy_texture() {
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

bool Renderer::has_texture() {
	// return texture == nullptr ? false : true;
	return true;
}
