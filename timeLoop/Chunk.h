#pragma once
#ifndef CHUNK
#define CHUNK

#include "Window.h"
#include "Tile.h"

class Chunk {
public:
    // === Constructor ===
    Chunk(float leftEdge, AppWindow window);

    // === Public Methods ===
    void append(Tile::TileType type, float x, float y, AppWindow appWindow);
    void update(float viewScale, float xOffset);
    void render(std::vector<float> screenDimensions);
    void set_debug(char a);

    // === Public Fields ===
    std::vector<Tile> chunk;
    Hitbox hitbox;

private:
    // === Internal State ===
    bool showBounding = true;
    float xOff = 0;
    int debug = 0;

    float scale = 1;

    SDL_Renderer* r;
};

#endif
