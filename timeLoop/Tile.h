#pragma once
#ifndef TILE
#define TILE

#include <SDL3/SDL.h>
#include "Window.h"
#include "Hitbox.h"
#include "Camera.h"



class Tile {
public:
    enum TileType {
        NILL,
        DIRT_LIGHT,
        DIRT_DARK,
        GRASS_LIGHT,
        GRASS_DARK
    };

    Tile(TileType tileType, float xPos, float yPos, AppWindow window, Camera &windowCamera);



    void handle_event(bool fullscreen);

    void update(float viewScale);

    void render();

private:
    float x, y;
    float w = 40; // width

    float fullscreenScale;

    float renderX, renderY, renderW;
    float scale;
    Camera &camera;
    
    Hitbox hitbox;
    TileType type;

    SDL_Renderer* r = nullptr;
    SDL_FRect t;

    void set_texture();
};




#endif