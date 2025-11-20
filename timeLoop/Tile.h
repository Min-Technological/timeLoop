#pragma once
#ifndef TILE
#define TILE

#include <SDL3/SDL.h>
#include <vector>
#include "Renderer.h"
#include "Hitbox.h"
#include "CameraDepth.h"

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
        CHARACTERSWAP_PENTACLE,

        TAROT_STATION,
    };

    // === Constructor ===
    Tile(TileType tileType, float xPos, float yPos, SDL_Renderer* r, float& s, float& depth);

    // === Public Methods ===
    void handle_event(bool fullscreen);
    void update(float offset);
    void render(std::vector<float> screenDimensions);

    Hitbox* get_hitbox();
    int get_type() const;

    // === Public Fields ===
    Hitbox hitbox;

private:
    // === Position & Size ===
    float x, y;
    float w = 40; // Width

    // === Render State ===
    Renderer renderer;

    // === Miscellaneous Tile Info ===
    TileType type;

};

#endif
