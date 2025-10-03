#pragma once
#ifndef CHUNK
#define CHUNK

#include "Window.h"
#include "Renderer.h"
#include "Tile.h"
#include "TarotCard.h"

class Chunk {
public:
    // === Constructor ===
    Chunk(float leftEdge, AppWindow window, float& s);

    // === Public Methods ===
    void append(Tile::TileType type, float x, float y, SDL_Renderer* renderer, float& s);
    void add_cards(int type, float x, float y, AppWindow appWindow, float& s);
    void remove_card(TarotCard* tarotCard);
    void update(float viewScale, float xOffset);
    void render(std::vector<float> screenDimensions);
    void set_debug(char a);

    // === Public Fields ===
    std::vector<Tile> chunk;
    std::vector<TarotCard*> cards;
    Hitbox hitbox;
    bool showBounding = false;

private:
    // === Internal State ===
    float x;
    float y = 0;
    float w = 640;
    float h = 2080;

    Renderer renderer;
    float scale = 1;
    int debug = 0;

};

#endif
