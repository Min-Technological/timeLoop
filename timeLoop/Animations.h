#pragma once
#ifndef ANIMATIONS
#define ANIMATIONS

#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Animations {
public:
    Animations(SDL_Texture* texture);

    void load_sprites(float y, float w, float h, int count);
    SDL_FRect& get_sprite(int frame);
    int get_total_frames() const;

private:
    SDL_Texture* t = NULL;
    std::vector<SDL_FRect> spriteRegions;

    int frameCount = 0;
};

#endif
