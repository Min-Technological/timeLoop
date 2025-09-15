#pragma once
#ifndef CHARACTER
#define CHARACTER

#include <SDL3/SDL.h>
#include <cmath>
#include <vector>
#include <array>
#include "Window.h"
#include "Input.h"
#include "Time.h"
#include "Renderer.h"
#include "Hitbox.h"
#include "Chunk.h"
#include "PassiveData.h"
#include "TarotDeck.h"

class Character {
public:
    // === Constructor ===
    Character(float x, float y, AppWindow window, Time& timer);

    // === Public Methods ===
    void handle_event(Input input);
    void move(Input input);
    void collide(std::vector<Chunk>& map);
    void update(float viewScale, float xOffset);
    void render();
    void destroy();

    int return_state() const;
    void load_data(PassiveData passive);

    std::array<float, 2> get_velocity() const;

    // === Public Fields ===
    Hitbox hitbox;
    bool bounding = false;  // Display Hitbox
    float w = 40; // Width
    float h = 160; // Height

private:
    // === Movement Helpers ===
    void move_up(int px);
    void move_left(int px);
    void move_down(int px);
    void move_right(int px);
    void move_jump();

    void increment_walk();

    // === Collision Helpers ===
    std::vector<Tile*> get_collided_tiles(std::vector<Chunk>& map) const;
    std::vector<TarotCard*> get_collided_tarot(std::vector<Chunk>& map);
    void solid_Y_collision(Tile& tile);
    void solid_X_collision(Tile& tile);

    // === Event Helpers ===
    void suicide();

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
    int walkingNum = 0;
    Uint64 walkFrameCounter = 0;
    int spriteColumn = 0;

    // === Persona Fields ===
    enum Persona {
        PROTAG,     // No Name
        CUP,        // TBD
        WAND,       // Velara
        SWORD,      // TBD
        PENTACLE    // TBD
    };
    Persona currentPersona = WAND;
    int personasUnlocked = 0;

    void change_persona(Persona persona);

        
    float newX; // Predicted x
    float newY; // Predicted y
    float scale = 1;    // Vertical Scale Multiplier (1 : 1080)

    AppWindow appWindow;    // Window
    Renderer renderer;
    Time& time;  // Timer

    bool grounded = true;   // On a platform
    bool sprinting = false; // Running

    float xVelocity = 0;
    float yVelocity = 0;
    float jumpVelocity = 20; // Initial Upward Velocity when Jumping
    float gravity = 1;  // Scalar - p/(f^2)

    // === Outside Communications ===
    bool stateChanged = false;
    int gameState = 1;

    // === UHHHH Tarot? ===
    TarotDeck tarotDeck;
};

#endif
