#pragma once
#ifndef CHUNK
#define CHUNK

#include "Window.h"
#include "Tile.h"

class Chunk {
public:
	Chunk(float leftEdge, AppWindow window);

	void append(Tile::TileType type, float x, float y, AppWindow appWindow);

	void update(float viewScale, float xOffset);

	void render(std::vector<float> screenDimensions);

	void set_debug(char a);

	std::vector<Tile> chunk;

	Hitbox hitbox;

private:
	bool showBounding = true;
	float xOff = 0;
	int debug = 0;

	SDL_Renderer* r;

	float scale = 1;
};


#endif
