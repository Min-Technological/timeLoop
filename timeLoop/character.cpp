#include "Character.h"

// === Constructor ===
Character::Character(float x, float y, float width, float height, AppWindow window)
    : w(width), h(height), newX(x), newY(y), appWindow(window), r(window.get_renderer()) {
    hitbox = std::move(Hitbox(x, y, width, height));
    fullscreenScale = SDL_GetWindowDisplayScale(window.get_window());
    set_texture(0);
}

// === Input & Movement ===
void Character::handle_event(bool fullscreen) {
    // Intentionally left empty or to be implemented
}

void Character::move() {
    newX = hitbox.xa;
    newY = hitbox.ya;

    bool yMoved = false;
    bool xMoved = false;

    const bool* keys = SDL_GetKeyboardState(NULL);

    sprinting = keys[SDL_SCANCODE_LSHIFT];

    if (keys[SDL_SCANCODE_W]) {
        // moveUp(10);
        // yMoved = true;
    }

    if (keys[SDL_SCANCODE_S]) {
        // moveDown(10);
        // yMoved = true;
    }

    if (keys[SDL_SCANCODE_A]) {
        moveLeft(10);
        xMoved = true;
    }

    if (keys[SDL_SCANCODE_D]) {
        moveRight(10);
        xMoved = true;
    }

    if (keys[SDL_SCANCODE_SPACE]) {
        moveJump();
    }

    if (keys[SDL_SCANCODE_R]) {
        newX = 960;
        xVelocity = 0;
        newY = 680;
        yVelocity = 0;
    }
}

// === Collision Handling ===
void Character::collide(std::vector<Chunk>& map) {
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
    scale = viewScale;
    xOff = xOffset;
    set_texture(xOffset);
}

void Character::render() {
    SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(r, &t);

    if (bounding) {
        std::cout << "BOUNDING\n";
        hitbox.render_hitbox(r, xOff, scale, 0);
    }
}

// === Movement Helpers ===
void Character::moveUp(int px) {
    yVelocity += sprinting ? px * 2 : px;
}

void Character::moveLeft(int px) {
    xVelocity -= sprinting ? px * 2 : px;
}

void Character::moveDown(int px) {
    yVelocity -= sprinting ? px * 2 : px;
}

void Character::moveRight(int px) {
    xVelocity += sprinting ? px * 2 : px;
}

void Character::moveJump() {
    if (grounded) {
        yVelocity = jumpVelocity;
        grounded = false;
    }
}

// === Texture / Render Helpers ===
void Character::set_texture(float xOffset) {
    renderX = (newX - xOffset) * scale;
    renderY = newY * scale;
    renderW = w * scale;
    renderH = h * scale;

    t = { renderX, renderY, renderW, renderH };
}

// === Collision Helpers ===
std::vector<Tile*> Character::get_collided_tiles(std::vector<Chunk>& map) {
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
