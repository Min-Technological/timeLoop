#include "Character.h"

// === Constructor ===
Character::Character(float initialX, float initialY, AppWindow window, Time& timer, float& s, float& depth)
    : x(initialX),
    y(initialY),
    newX(initialX),
    newY(initialY),
    renderer(window.get_renderer(), initialX, initialY, w, h, s, depth),
    time(timer),
    health(5, 30)
{
    hitbox = std::move(Hitbox(initialX, initialY, w, h));
    change_persona(currentPersona);
    attackManager.set_damage(1);
}

void Character::move(Input input) {

    std::array currentPos = hitbox.get_current_pos();

    newX = currentPos[0];
    newY = currentPos[1];
    xVelocity = xVelocity * 0.75f;
    yVelocity += gravity;

    bool yMoved = false;
    bool xMoved = false;

    sprinting = input.is_key_pressed(SDL_SCANCODE_LSHIFT);

    if (input.is_key_pressed(SDL_SCANCODE_A)) {
        move_left(2); // === Previously used 2 ===
        xMoved = true;
    }

    if (input.is_key_pressed(SDL_SCANCODE_D)) {
        move_right(2); // === Previously used 2 ===
        xMoved = true;
    }



    if (input.is_key_just_pressed(SDLK_COMMA)) {
        if (!cooldown)
        {
            if (!facingLeft) {
                attackManager.set_rect_attack(x + w, y, 160, 160);

            }
            else if (facingLeft) {
                attackManager.set_rect_attack(x - 160, y, 160, 160);
            }

            
            attacking = true;
            cooldown = true;
            attackTime = time.current_frame();
        }
    }
    else if (attacking) {
        xVelocity = 0;
    }



    if (input.is_key_pressed(SDL_SCANCODE_SPACE)) {
        move_jump();
    }
    else if (!input.is_key_pressed(SDL_SCANCODE_SPACE) && jumping == true) {
        yVelocity = yVelocity * 0.7f;
    }

    if (yVelocity >= 0) {
        jumping = false;
    }

    newX += xVelocity;
    newY += yVelocity;

    hitbox.update_hitbox(newX, newY, w, h);
}

void Character::resolve_collision() {
    std::array<float, 4> userPos = hitbox.get_current_pos();
    x = userPos[0];
    y = userPos[1];
}

// === Update & Render ===
void Character::update(float xOffset, float yOffset) {

    switch (currentState) {
    case AnimationState::WALKING_RIGHT:
        spriteColumn = 0;
        renderer.new_position(x - w, y, 120.0f, h, xOffset, yOffset);
        break;

    case AnimationState::WALKING_LEFT:
        spriteColumn = 1;
        renderer.new_position(x - w, y, 120.0f, h, xOffset, yOffset);
        break;

    case AnimationState::RUNNING_RIGHT:
        spriteColumn = 2;
        renderer.new_position(x - w, y, 120.0f, h, xOffset, yOffset);
        break;

    case AnimationState::RUNNING_LEFT:
        spriteColumn = 3;
        renderer.new_position(x - w, y, 120.0f, h, xOffset, yOffset);
        break;

    default:
        spriteColumn = 0;
        renderer.new_position(x - w, y, 120.0f, h, xOffset, yOffset);
        break;
    }

    if (cooldown) {
        if (time.current_frame() - attackTime >= 30) {
            cooldown = false;
            attacking = false;
        }
        else if (time.current_frame() - attackTime >= 6) {
            attacking = false;
            attackManager.despawn_attack();
        }
        std::cout << "COOLDOWN: " << (30 - (time.current_frame() - attackTime)) << "\n";
    }

    if (health.is_invincible(time.current_frame())) {
        if (time.current_frame() % 10 < 5) {
            alphaValue = 0xbe;
        }
        else {
            alphaValue = 0x5f;
        }
        renderer.set_alpha(alphaValue);
    }
    else {
        if (alphaValue != 0xff) {
            alphaValue = 0xff;
            renderer.set_alpha(alphaValue);
        }
    }
    
}

void Character::render() {


    renderer.render_sprite(60.0f * walkingNum, 80.0f * spriteColumn, 60, 80);
    // SDL_RenderFillRect(r, &v);

    if (bounding) {
        hitbox.render(&renderer);
    }
}

void Character::destroy() {
    renderer.destroy_texture();
}



void Character::change_persona(Persona persona) {
    renderer.destroy_texture();
    currentPersona = persona;
    switch (persona) {
    case Persona::PROTAG:
        renderer.load_texture("charProtagonist.png");
        break;
    case Persona::WAND:
        renderer.load_texture("charVelara.png");
        break;
    case Persona::CUP:
        renderer.load_texture("charRachel.png");
        break;
    case Persona::SWORD:
        renderer.load_texture("charAmber.png");
        break;
    case Persona::PENTACLE:
        renderer.load_texture("charEmma.png");
        break;
    default:
        std::cout << "NO CHARACTER SELECTED!\n";
        break;
    }
}

Persona Character::get_persona() {
    return currentPersona;
}

void Character::save_data(PassiveData* passiveData) {

    std::array<float, 4> currentPos = hitbox.get_current_pos();

    passiveData->set_player_postition(
        currentPos[0],
        currentPos[1],
        xVelocity,
        yVelocity
    );

    passiveData->set_persona(currentPersona);
}

void Character::load_data(PassiveData* passiveData) {
    std::array<float, 4> playerPos = passiveData->get_player_position();

    hitbox.update_hitbox(playerPos[0], playerPos[1], w, h);
    xVelocity = playerPos[2];
    yVelocity = playerPos[3];

    this->change_persona(static_cast<Persona>(passiveData->get_persona()));

}

void Character::set_velocity(float x, float y) {
    xVelocity = x;
    yVelocity = y;
}

std::array<float, 2> Character::get_velocity() const {
    return { xVelocity, yVelocity };
}

Hitbox* Character::get_hitbox() {
    return &hitbox;
}



void Character::landed() {
    yVelocity = 0;
    grounded = true;

}

void Character::hit_head() {
    yVelocity = 0;

}

void Character::hit_left() {
    xVelocity = 0;

}

void Character::hit_right() {
    xVelocity = 0;

}



Attack* Character::get_attack() {
    return &attackManager;
}

float Character::get_health() {
    return health.get_hp();
}

void Character::damage(float damage) {
    health.damage(damage, time.current_frame());
}

void Character::revive() {
    health.revive();
}




// === Movement Helpers ===
void Character::move_up(int px) {
    yVelocity += sprinting ? px * 2 : px;
}

void Character::move_left(float px) {
    facingLeft = true;
    xVelocity -= sprinting ? px * 2 : px;

    currentState = sprinting ? AnimationState::RUNNING_LEFT : AnimationState::WALKING_LEFT;
    increment_walk();
}

void Character::move_down(int px) {
    yVelocity -= sprinting ? px * 2 : px;
}

void Character::move_right(float px) {
    facingLeft = false;
    xVelocity += sprinting ? px * 2 : px;

    currentState = sprinting ? AnimationState::RUNNING_RIGHT : AnimationState::WALKING_RIGHT;
    increment_walk();
}

void Character::move_jump() {
    if (grounded) {
        yVelocity = jumpVelocity;
        jumping = true;
        grounded = false;
    }
}

void Character::increment_walk() {
    // Current time since SDL Initialized
    Uint64 currentTime = time.current_time();

    // How many ms has passed since last frame
    Uint64 difference = currentTime - walkFrameCounter;

    // 30 fps cap
    if (difference > 33) {
        walkFrameCounter = currentTime;

        walkingNum++;
        if (!(walkingNum < 12)) {
            walkingNum = 0;
        }
    }
}

