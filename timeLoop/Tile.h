#pragma once
#ifndef TILE
#define TILE

#include <SDL3/SDL.h>
#include <vector>
#include "Renderer.h"
#include "Hitbox.h"

class Tile {
public:
    // === Tile Types ===
    enum TileType {
        NILL,
        DIRT_LIGHT,
        DIRT_DARK,
        GRASS_LIGHT,
        GRASS_DARK,
        CHARACTERSWAP_PROTAG,
        CHARACTERSWAP_CUP,
        CHARACTERSWAP_SWORD,
        CHARACTERSWAP_WAND,
        CHARACTERSWAP_PENTACLE
    };

    // === Constructor ===
    Tile(TileType tileType, float xPos, float yPos, SDL_Renderer* r, float& s);

    // === Public Methods ===
    void handle_event(bool fullscreen);
    void update(float viewScale, float offset);
    void render(std::vector<float> screenDimensions);

    int get_type() const;

    // === Public Fields ===
    Hitbox hitbox;

private:
    // === Position & Size ===
    float x, y;
    float w = 40; // Width

    // === Render State ===
    Renderer renderer;
    float scale = 1;

    // === Miscellaneous Tile Info ===
    TileType type;

};

#endif
