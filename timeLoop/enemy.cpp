#include "Enemy.h"


// === Constructor ===
Enemy::Enemy(float initialX, float initialY, AppWindow window, Time& timer, float& s, float& depth)
    : x(initialX),
    y(initialY),
    newX(initialX),
    newY(initialY),
    renderer(window.get_renderer(), initialX, initialY, w, h, s, depth),
    w(80),
    h(160),
    health(10, 10, timer)
    // time(timer)
{
    hitbox = std::move(Hitbox(initialX, initialY, w, h));
}

void Enemy::update(float xOffset, float yOffset) {
    if (health.get_death()) return;


    renderer.new_position(x, y, w, h, xOffset, yOffset);
}

void Enemy::render() {
    if (health.get_death()) return;

    renderer.render_colour(tempR, 0x00, tempB, 0xff);

    tempR = 0x80;
    tempB = 0xff;
}


Hitbox* Enemy::get_hitbox() {
    // if (health.get_death()) return nullptr;

    return &hitbox;
}

void Enemy::take_damage(float damage) {

    health.damage(damage);

    tempR = 0xff;
    tempB = 0x00;

    std::cout << nameID << " took " << damage << " dmg!... " << health.get_hp() << "HP Left!\n";

    if (health.get_death()) die();

}


void Enemy::die() {
    hitbox.enable_collisions(false);
}



