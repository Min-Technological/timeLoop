#include "Character.h"

// === Constructor ===
Character::Character(float x, float y, float width, float height, AppWindow window, Time& timer)
    : w(width), h(height), newX(x), newY(y), appWindow(window), r(window.get_renderer()), time(timer) {
    hitbox = std::move(Hitbox(x, y, width, height));
    load_all_sprites();
    set_texture(0);
}

// === Input & Movement ===
void Character::handle_event(SDL_Event* e) {
    stateChanged = false;
    gameState = 1;

    if (e->type == SDL_EVENT_KEY_DOWN) {
        if (e->key.key == SDLK_R) {
            suicide();
        }
    }
}

void Character::move() {
    if (stateChanged) {
        return;
    }

    newX = hitbox.xa;
    newY = hitbox.ya;

    bool yMoved = false;
    bool xMoved = false;

    const bool* keys = SDL_GetKeyboardState(NULL);

    sprinting = keys[SDL_SCANCODE_LSHIFT];

    if (keys[SDL_SCANCODE_W]) {
        // move_up(10);
        // yMoved = true;
    }

    if (keys[SDL_SCANCODE_S]) {
        // move_down(10);
        // yMoved = true;
    }

    if (keys[SDL_SCANCODE_A]) {
        move_left(10);
        xMoved = true;
    }

    if (keys[SDL_SCANCODE_D]) {
        move_right(10);
        xMoved = true;
    }

    if (keys[SDL_SCANCODE_SPACE]) {
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
    xVelocity = 0;

    hitbox.update_hitbox(newX, newY, w, h);
}

// === Update & Render ===
void Character::update(float viewScale, float xOffset) {
    if (stateChanged) {
        return;
    }

    scale = viewScale;
    xOff = xOffset;
    set_texture(xOffset);
}

void Character::render() {
    if (stateChanged) {
        return;
    }

    SDL_RenderTexture(r, t, currentSprite, &v);
    // SDL_RenderFillRect(r, &v);

    if (bounding) {
        hitbox.render_hitbox(r, xOff, scale, 0);
    }
}

void Character::destroy() {
    if (t) {
        SDL_DestroyTexture(t);
        t = nullptr;
    }
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
    int difference = currentTime - walkFrameCounter;

    // 30 fps cap
    if (difference > 33) {
        walkFrameCounter = currentTime;

        walkingNum++;
        if (!(walkingNum < 12)) {
            walkingNum = 0;
        }
    }
}

// === Texture / Render Helpers ===
void Character::load_texture(const std::string& path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        std::cout << "UNABLE TO LOAD IMAGE! " << SDL_GetError() << std::endl;
        return;
    }

    t = SDL_CreateTextureFromSurface(r, loadedSurface);
    if (!t) {
        std::cout << "UNABLE TO CREATE TEXTURE FROM: " << SDL_GetError() << std::endl;
    }
    else {
        SDL_SetTextureScaleMode(t, SDL_SCALEMODE_NEAREST);
    }



    SDL_DestroySurface(loadedSurface);
}

void Character::load_all_sprites() {
    const std::string path = "protagonist.png";
    load_texture(path);

    for (int i = 0; i < static_cast<int>(TOTAL); i++) {
        animations.emplace_back(t);
        switch (i) {
        case (static_cast<int>(WALKING_RIGHT)):
            animations[i].load_sprites((0 * 80), 60, 80, 12);
            break;
        case (static_cast<int>(WALKING_LEFT)):
            animations[i].load_sprites((1 * 80), 60, 80, 12);
            break;
        case (static_cast<int>(RUNNING_RIGHT)):
            animations[i].load_sprites((2 * 80), 60, 80, 12);
            break;
        case (static_cast<int>(RUNNING_LEFT)):
            animations[i].load_sprites((3 * 80), 60, 80, 12);
            break;
        default:
            break;
        }
    }
}

void Character::set_texture(float xOffset) {
    renderX = (newX - xOffset) * scale;
    renderY = newY * scale;
    renderW = w * scale;
    renderH = h * scale;

    v = { renderX, renderY, renderW, renderH };

    switch (currentState) {
    case State::WALKING_LEFT:
    case State::WALKING_RIGHT:
    case State::RUNNING_LEFT:
    case State::RUNNING_RIGHT:
        v.x -= 40 * scale;
        v.w = 120 * scale;
        break;
    default:
        break;
    }

    currentSprite = &animations[static_cast<int>(currentState)].get_sprite(walkingNum);

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
}
