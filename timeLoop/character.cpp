#include "Character.h"

// === Constructor ===
Character::Character(float initialX, float initialY, AppWindow window, Time& timer, float& s)
    : newX(initialX), 
    newY(initialY), 
    renderer(window.get_renderer(), initialX, initialY, w, h, s), 
    time(timer)
{
    hitbox = std::move(Hitbox(initialX, initialY, w, h));
    change_persona(currentPersona);
}

void Character::move(Input input) {

    std::array currentPos = hitbox.get_current_pos();

    newX = currentPos[0];
    newY = currentPos[1];
    xVelocity = xVelocity * 0.75;
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

    if (input.is_key_pressed(SDL_SCANCODE_SPACE)) {
        move_jump();
        if (yVelocity <= 0) {
            jumping = false;
        }
    }
    else if (!input.is_key_pressed(SDL_SCANCODE_SPACE) && jumping == true) {
        yVelocity = 0;
        jumping = false;
    }

    newX += xVelocity;
    newY += yVelocity;

    hitbox.update_hitbox(newX, newY, w, h);
}

// === Update & Render ===
void Character::update(float viewScale, float offset) {

    if (scale != viewScale) {
        scale = viewScale;
    }

    renderer.new_position(newX, newY, w, h, offset);

    switch (currentState) {
    case AnimationState::WALKING_RIGHT:
        spriteColumn = 0;
        renderer.new_position(newX - 40, newY, 120, h, offset);
        break;

    case AnimationState::WALKING_LEFT:
        spriteColumn = 1;
        renderer.new_position(newX - 40, newY, 120, h, offset);
        break;

    case AnimationState::RUNNING_RIGHT:
        spriteColumn = 2;
        renderer.new_position(newX - 40, newY, 120, h, offset);
        break;

    case AnimationState::RUNNING_LEFT:
        spriteColumn = 3;
        renderer.new_position(newX - 40, newY, 120, h, offset);
        break;

    default:
        spriteColumn = 0;
        renderer.new_position(newX, newY, w, h, offset);
        break;
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

std::array<float, 2> Character::get_velocity() const {
    return { xVelocity, yVelocity };
}



// === Movement Helpers ===
void Character::move_up(int px) {
    yVelocity += sprinting ? px * 2 : px;
}

void Character::move_left(int px) {
    xVelocity -= sprinting ? px * 2 : px;

    currentState = sprinting ? AnimationState::RUNNING_LEFT : AnimationState::WALKING_LEFT;
    increment_walk();
}

void Character::move_down(int px) {
    yVelocity -= sprinting ? px * 2 : px;
}

void Character::move_right(int px) {
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

