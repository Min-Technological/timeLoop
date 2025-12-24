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
#include "Attack.h"
#include "CameraDepth.h"
#include "PassiveData.h"
#include "Enums.h"
#include "Health.h"

class Character {
public:
    // === Constructor ===
    Character(float initialX, float initialY, AppWindow window, Time& timer, float& s, float& depth);

    // === Public Methods ===
    void handle_event(Input input);
    void move(Input input);
    void resolve_collision();
    void update(float xOffset, float yOffset);
    void render();
    void destroy();


    // === Data-Based Helpers ===
    void change_persona(Persona persona);
    Persona get_persona();

    void save_data(PassiveData *passiveData);
    void load_data(PassiveData* passiveData);
    
    // === Collision/Movement Helpers ===
    void set_velocity(float x, float y);
    std::array<float, 2> get_velocity() const;
    Hitbox* get_hitbox();

    void landed();
    void hit_head();
    void hit_left();
    void hit_right();


    Attack* get_attack();
    float get_health();
    void damage(float damage);
    void revive();



    // === Public Fields ===
    Hitbox hitbox;
    bool bounding = false;  // Display Hitbox
    float w = 40;   // Width
    float h = 160;  // Height

private:
    // === Movement Helpers ===
    void move_up(int px);
    void move_left(float px);
    void move_down(int px);
    void move_right(float px);
    void move_jump();

    Health health;

    Attack attackManager;
    bool attacking = false;
    bool cooldown = false;
    Uint64 attackTime = 0;


    // === Rendering Fields ===
    // --- Essential Variables ---
    Renderer renderer;  // Rendering Management
    Time& time;         // Time Management

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
    
    Uint8 alphaValue = 0xff;

    void increment_walk();



    // === Persona Fields ===
    Persona currentPersona = Persona::PROTAG;
    std::array<bool, 5> personasUnlocked = { 1, 1, 1, 1, 1 };

 

    // === Physics Data ===
    bool facingLeft = false;
    
    // --- Location ---
    float newX; // Predicted x
    float newY; // Predicted y
    float x;        // Left Position
    float y;        // Top Position

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
