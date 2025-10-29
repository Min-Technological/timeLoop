#pragma once
#ifndef RENDERER
#define RENDERER

#include <SDL3/SDL.h>
#include <SDL3_image\SDL_image.h>
#include <iostream>
#include <vector>

class Renderer {
public:
	Renderer(SDL_Renderer* r, float x, float y, float w, float h, float& s);

	void load_texture(const std::string &path);

	void new_position(float newX, float newY, float newW, float newH, float xOff);

	bool test_frame(std::vector<float> camera) const;

	void render_colour(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	void render_texture();
	void render_sprite(float x, float y, float w, float h);
	void render_hitbox(float xa, float ya, float xb, float yb, Uint8 green);
	void render_clickbox(float x, float y, float w, float h, Uint8 green);

	void destroy_texture();

	bool has_texture();
private:

	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_FRect viewport;

	float& scale;
	float xOffset = 0;
};

#endif