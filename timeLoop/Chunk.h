#pragma once
#ifndef CHUNK
#define CHUNK

#include "Window.h"
#include "Tile.h"
#include "TarotCard.h"

class Chunk {
public:
    // === Constructor ===
    Chunk(float leftEdge, AppWindow window);

    // === Public Methods ===
    void append(Tile::TileType type, float x, float y, SDL_Renderer* renderer);
    void add_cards(int type, float x, float y, AppWindow appWindow);
    void update(float viewScale, float xOffset);
    void render(std::vector<float> screenDimensions);
    void set_debug(char a);

    // === Public Fields ===
    std::vector<Tile> chunk;
    std::vector<TarotCard> cards;
    Hitbox hitbox;
    bool showBounding = false;

private:
    // === Internal State ===
    float xOff = 0;
    int debug = 0;

    float scale = 1;

    SDL_Renderer* r;
};

#endif
