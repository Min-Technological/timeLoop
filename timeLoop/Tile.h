#pragma once
#ifndef TILE
#define TILE

#include <SDL3/SDL.h>
#include <vector>
#include "Window.h"
#include "Hitbox.h"

class Tile {
public:
    // === Tile Types ===
    enum TileType {
        NILL,
        DIRT_LIGHT,
        DIRT_DARK,
        GRASS_LIGHT,
        GRASS_DARK
    };

    // === Constructor ===
    Tile(TileType tileType, float xPos, float yPos, AppWindow window);

    // === Public Methods ===
    void handle_event(bool fullscreen);
    void update(float viewScale, float offset);
    void render(std::vector<float> screenDimensions);
    int get_type();

    // === Public Fields ===
    Hitbox hitbox;

private:
    // === Position & Size ===
    float x, y;
    float w = 40; // Width

    // === Render State ===
    float fullscreenScale;
    float renderX, renderY, renderW;
    float scale;

    TileType type;

    SDL_Renderer* r = nullptr;
    SDL_FRect t;

    // === Private Helpers ===
    void set_texture();
};

#endif
