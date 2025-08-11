#include "Character.h"

// === Constructor ===
Character::Character(float x, float y, AppWindow window, Time& timer)
    : newX(x), newY(y), appWindow(window), renderer(window.get_renderer(), x, y, w, h), time(timer) {
    hitbox = std::move(Hitbox(x, y, w, h));
    renderer.load_texture("protagonist.png");
}

// === Input & Movement ===
void Character::handle_event(Input input) {
    stateChanged = false;
    gameState = 1;

    if (input.is_key_just_pressed(SDLK_R)) {
        suicide();
    }
}

void Character::move(Input input) {
    if (stateChanged) {
        return;
    }

    newX = hitbox.xa;
    newY = hitbox.ya;

    bool yMoved = false;
    bool xMoved = false;

    sprinting = input.is_key_pressed(SDL_SCANCODE_LSHIFT);

    if (input.is_key_pressed(SDL_SCANCODE_A)) {
        move_left(2);
        xMoved = true;
    }

    if (input.is_key_pressed(SDL_SCANCODE_D)) {
        move_right(2);
        xMoved = true;
    }

    if (input.is_key_pressed(SDL_SCANCODE_SPACE)) {
        move_jump();
    }
}

// === Collision Handling ===
void Character::collide(std::vector<Chunk>& map) {
    if (stateChanged) {
        return;
    }

    newY -= yVelocity;
    hitbox.update_hitbox(newX, newY, w, h);
    grounded = false;

    // Y-axis collision
    std::vector<Tile*> collidedTiles = get_collided_tiles(map);
    for (Tile* tile : collidedTiles) {
        int responseType = tile->get_type();
        if (responseType == 0) continue;

        switch (responseType) {
        case 1: // Dirt Light
        case 2: // Dirt Dark
        case 3: // Grass Light
        case 4: // Grass Dark
            solid_Y_collision(*tile);
            break;
        default:
            break;
        }
    }

    if (grounded) {
        yVelocity = 0;
    }
    else {
        yVelocity += (-gravity);
        if (yVelocity < -40) {
            yVelocity = -40;
        }
    }

    if (xVelocity == 0) {
        walkingNum = 0;
    }
    newX += xVelocity;
    hitbox.update_hitbox(newX, newY, w, h);

    // X-axis collision
    collidedTiles = get_collided_tiles(map);
    for (Tile* tile : collidedTiles) {
        int responseType = tile->get_type();
        if (responseType == 0) continue;

        switch (responseType) {
        case 1: // Dirt Light
        case 2: // Dirt Dark
        case 3: // Grass Light
        case 4: // Grass Dark
            solid_X_collision(*tile);
            break;
        default:
            break;
        }
    }
    xVelocity = xVelocity * 0.8f;

    hitbox.update_hitbox(newX, newY, w, h);
}

// === Update & Render ===
void Character::update(float viewScale, float offset) {
    if (stateChanged) {
        return;
    }

    if (scale != viewScale) {
        scale = viewScale;
        renderer.new_scale(scale);
    }

    renderer.new_position(newX, newY, w, h, offset);

    switch (currentState) {
    case State::WALKING_RIGHT:
        spriteColumn = 0;
        renderer.new_position(newX - 40, newY, 120, h, offset);
        break;

    case State::WALKING_LEFT:
        spriteColumn = 1;
        renderer.new_position(newX - 40, newY, 120, h, offset);
        break;

    case State::RUNNING_RIGHT:
        spriteColumn = 2;
        renderer.new_position(newX - 40, newY, 120, h, offset);
        break;

    case State::RUNNING_LEFT:
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
    if (stateChanged) {
        return;
    }

    renderer.render_sprite(60.0f * walkingNum, 80.0f * spriteColumn, 60, 80);
    // SDL_RenderFillRect(r, &v);

    if (bounding) {
        renderer.render_hitbox(hitbox, 0);
    }
}

void Character::destroy() {
    renderer.destroy_texture();
}

int Character::return_state() const {
    return gameState;
}

void Character::load_data(PassiveData passive) {
    hitbox.update_hitbox(passive.x, passive.y, w, h);
    xVelocity = passive.xVelocity;
    yVelocity = passive.yVelocity;
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

    currentState = sprinting ? State:: RUNNING_LEFT : State::WALKING_LEFT;
    increment_walk();
}

void Character::move_down(int px) {
    yVelocity -= sprinting ? px * 2 : px;
}

void Character::move_right(int px) {
    xVelocity += sprinting ? px * 2 : px;

    currentState = sprinting ? State::RUNNING_RIGHT : State::WALKING_RIGHT;
    increment_walk();
}

void Character::move_jump() {
    if (grounded) {
        yVelocity = jumpVelocity;
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

// === Event Helpers ===
void Character::suicide() {
    stateChanged = true;
    gameState = 3;
}

// === Collision Helpers ===
std::vector<Tile*> Character::get_collided_tiles(std::vector<Chunk>& map) const {
    std::vector<Tile*> collidedTiles;

    for (Chunk& chunk : map) {
        if (!hitbox.check_collision(chunk.hitbox)) {
            chunk.set_debug('R');
            continue;
        }

        chunk.set_debug('G');
        for (Tile& tile : chunk.chunk) {
            if (hitbox.check_collision(tile.hitbox)) {
                collidedTiles.push_back(&tile);
            }
        }
    }

    return collidedTiles;
}

void Character::solid_Y_collision(Tile& tile) {
    if (yVelocity < 0) {
        newY = tile.hitbox.ya - h;
        grounded = true;
    }
    else if (yVelocity > 0) {
        newY = tile.hitbox.yb;
        yVelocity = 0;
    }
}

void Character::solid_X_collision(Tile& tile) {
    if (xVelocity < 0) {
        newX = tile.hitbox.xb;
    }
    else if (xVelocity > 0) {
        newX = tile.hitbox.xa - w;
    }
    walkingNum = 0;
}
