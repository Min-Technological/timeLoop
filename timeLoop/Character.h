#pragma once
#ifndef CHARACTER
#define CHARACTER

#include <SDL3/SDL.h>
#include <vector>
#include "Window.h"
#include "Hitbox.h"
#include "Chunk.h"

class Character {
public:
    // === Constructor ===
    Character(float x, float y, float width, float height, AppWindow window);

    // === Public Methods ===
    void handle_event(bool fullscreen);
    void move();
    void collide(std::vector<Chunk>& map);
    void update(float viewScale, float xOffset);
    void render();

    // === Public Fields ===
    Hitbox hitbox;
    float renderX, renderY;
    float w; // Width
    float h; // Height

private:
    // === Movement Helpers ===
    void moveUp(int px);
    void moveLeft(int px);
    void moveDown(int px);
    void moveRight(int px);
    void moveJump();

    // === Collision Helpers ===
    std::vector<Tile*> get_collided_tiles(std::vector<Chunk>& map);
    void solid_Y_collision(Tile& tile);
    void solid_X_collision(Tile& tile);

    // === Texture Helpers ===
    void set_texture(float xOffset);

    // === State Fields ===
    float newX; // Predicted x
    float newY; // Predicted y
    float renderW, renderH;
    float fullscreenScale;
    float scale;

    SDL_FRect t;          // Texture rect
    SDL_Renderer* r;      // Renderer
    AppWindow appWindow;

    bool grounded = true;
    bool sprinting = false;
    bool bounding = false;

    float xVelocity = 0;
    float yVelocity = 0;
    float jumpVelocity = 20;
    float gravity = 1;
    float xOff;
};

#endif
