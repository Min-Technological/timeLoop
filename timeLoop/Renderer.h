#pragma once
#ifndef RENDERER
#define RENDERER

#include <SDL3/SDL.h>
#include <SDL3_image\SDL_image.h>
#include <iostream>
#include <vector>
#include <array>
#include "CameraDepth.h"

class Renderer {
public:
	Renderer(SDL_Renderer* r, float x, float y, float w, float h, float& s, float& depth);

	void load_texture(const std::string &path);
	std::array<int, 2> texture_dimensions();

	void new_position(float newX, float newY, float newW, float newH, float xOff, float yOff);
	void rescale();
	void set_x_offset(float xOff);
	void set_y_offset(float yOff);
	void set_alpha(Uint8 alpha);

	bool test_frame(std::vector<float> camera) const;

	void render_colour(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	void render_texture();
	void render_sprite(float x, float y, float w, float h);
	void render_hitbox(float xa, float ya, float xb, float yb, Uint8 green);
	void render_clickbox(float x, float y, float w, float h, Uint8 green);

	void render_line(float x1, float y1, float x2, float y2);

	void render_triangle(std::array<SDL_Vertex, 3> triangle);

	// === Text Rendering ===
	void load_textbox(SDL_Surface* textSurface);

	void destroy_texture();

	bool has_texture();
private:

	SDL_Texture* texture = nullptr;
	SDL_Texture* scaledTexture = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_FRect viewport;

	CameraDepth cameraDepth;

	float& scale;
	float xOffset = 0;
	float yOffset = 0;

};

#endif