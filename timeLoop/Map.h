#pragma once
#ifndef MAP
#define MAP

#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Window.h"
#include "Tile.h"
#include "Camera.h"



class Map{
public:
	Map(const std::string& path, int tileWidth, AppWindow window, Camera &windowCamera);

	std::vector<Tile> generate_map();

private:
	std::string mapPath;
	SDL_Surface* s = nullptr;

	int tileSize;
	SDL_Renderer* r = nullptr;
	AppWindow appWindow;

	std::vector<Tile> map;

	SDL_Surface* load_surface();
	void create_tile(Uint32 color, float x, float y);

	Camera &camera;

};



#endif