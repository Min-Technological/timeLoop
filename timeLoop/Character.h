#pragma once
#ifndef CHARACTER
#define CHARACTER

#include <SDL3/SDL.h>
#include <cmath>
#include <vector>
#include <array>

#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Time.h"
#include "Hitbox.h"
#include "PassiveData.h"
#include "Enums.h"

class Character {
public:
    // === Constructor ===
    Character(float initialX, float initialY, AppWindow window, Time& timer, float& s);

    // === Public Methods ===
    void handle_event(Input input);
    void move(Input input);
    void update(float viewScale, float xOffset);
    void render();
    void destroy();

    void change_persona(Persona persona);
    Persona get_persona();

    void save_data(PassiveData *passiveData);
    void load_data(PassiveData* passiveData);
    

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




    // === Rendering Fields ===
    // --- Essential Variables ---
    Renderer renderer;  // Rendering Management
    Time& time;         // Time Management
    float scale = 1;    // Vertical Scale Multiplier (1 : 1080)

    // --- Animation ---
    enum AnimationState {     // List of Animation States   
        IDLE,   
        WALKING_RIGHT,
        WALKING_LEFT,
        RUNNING_RIGHT,
        RUNNING_LEFT,
        JUMPING,
        TOTAL // Total number of Animation States
    };
    AnimationState currentState = WALKING_RIGHT;
    Uint64 walkFrameCounter = 0;
    int walkingNum = 0;     // Frame Count
    int spriteColumn = 0;   

    void increment_walk();



    // === Persona Fields ===
    Persona currentPersona = Persona::PROTAG;
    std::array<bool, 5> personasUnlocked = { 1, 1, 1, 1, 1 };

 

    // === Physics Data ===
    // --- Location ---
    float newX; // Predicted x
    float newY; // Predicted y

    // --- Velocity ---
    float xVelocity = 0;
    float yVelocity = 0;
    bool sprinting = false; // Running

    // --- Jumping ---
    bool jumping = false; // Generating Upward Velocity
    bool grounded = true;   // On a platform
    float jumpVelocity = -20; // Initial Upward Velocity when Jumping
    float gravity = 1;  // Scalar - p/(f^2)



    // === PROTAG ABILITIES ===

    // === WANDS ABILITIES ===

    // === PENTACLES ABILITIES ===

    // === CUPS ABILITIES ===

    // === SWORDS ABILITIES ===
};

#endif
