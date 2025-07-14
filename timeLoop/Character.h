#pragma once
#ifndef CHARACTER
#define CHARACTER

#include <SDL3/SDL.h>
#include <vector>
#include "Window.h"
#include "Animations.h"
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
    void destroy();

    // === Public Fields ===
    Hitbox hitbox;
    float renderX, renderY;
    float w; // Width
    float h; // Height
    bool bounding = false;  // Display Hitbox

private:
    // === Movement Helpers ===
    void move_up(int px);
    void move_left(int px);
    void move_down(int px);
    void move_right(int px);
    void move_jump();

    void increment_walk();

    // === Collision Helpers ===
    std::vector<Tile*> get_collided_tiles(std::vector<Chunk>& map);
    void solid_Y_collision(Tile& tile);
    void solid_X_collision(Tile& tile);

    // === Texture Helpers ===
    void load_texture(const std::string& path);
    void load_all_sprites();
    void set_texture(float xOffset);

    // === State Fields ===
    enum State {    // List of Animation States
        IDLE,   
        WALKING_RIGHT,
        WALKING_LEFT,
        RUNNING_RIGHT,
        RUNNING_LEFT,
        JUMPING,
        TOTAL // Total number of Animation States
    };
    State currentState = WALKING_RIGHT;
    std::vector<Animations> animations;
    int walkingNum = 0;
    int walkFrameCounter = 0;
        
    float newX; // Predicted x
    float newY; // Predicted y
    float renderW, renderH; // Render Coordinates
    float scale;    // Vertical Scale Multiplier (1 : 1080)

    SDL_Texture* t = NULL;  // Protag Texture
    SDL_FRect v;            // Texture Viewport
    SDL_FRect* currentSprite = NULL;   // The current Sprite
    SDL_Renderer* r;        // Renderer
    AppWindow appWindow;    // Window

    bool grounded = true;   // On a platform
    bool sprinting = false; // Running

    float xVelocity = 0;
    float yVelocity = 0;
    float jumpVelocity = 20; // Initial Upward Velocity when Jumping
    float gravity = 1;  // Scalar - p/(f^2)
    float xOff;     // Camera Offset (x-axis)
};

#endif
