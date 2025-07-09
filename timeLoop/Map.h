#pragma once
#ifndef MAP
#define MAP

#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Window.h"
#include "Chunk.h"
#include "Tile.h"
#include "Camera.h"

class Map {
public:
    // === Constructor ===
    Map(const std::string& path, int tileWidth, AppWindow window, Camera& windowCamera);

    // === Public Methods ===
    std::vector<Chunk> generate_map();

private:
    // === File & Surface State ===
    std::string mapPath;
    SDL_Surface* s = nullptr;

    // === Map Properties ===
    int tileSize;
    AppWindow appWindow;
    SDL_Renderer* r = nullptr;
    std::vector<Chunk> map;

    // === Camera Reference ===
    Camera& camera;

    // === Private Helpers ===
    SDL_Surface* load_surface();
    void create_tile(Uint32 color, float x, float y, int mapIndex);
};

#endif
