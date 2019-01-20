#include "Player.hpp"

#include "../Constants.hpp"
#include "../Input.hpp"
#include "Bullets.hpp"

#include <iostream>

Y65535::Player::Player()
    : position(0.0f)
    , velocity(0.0f, 0.0f, -Constants::playerSpeed)
    , tSinceShoot(0.0f) {
}

void Y65535::Player::Step(float dt, Input const& i, Bullets& bullets) {
    Look(i);
    Travel(dt, i);
    Shoot(dt, i, bullets);
}

void Y65535::Player::Look(Input const& i) {
    velocity = glm::rotateY(velocity, glm::radians(-i.lookDx / 2.0f));
    velocity = glm::rotateX(velocity, glm::radians(-i.lookDy / 2.0f));
}

void Y65535::Player::Travel(float dt, Input const& i) {
    position += dt * velocity;

    // FIXME: Move perpendicular to the velocity.
    if (i.strafeUp)    position.y += dt * Constants::playerStrafe;
    if (i.strafeDown)  position.y -= dt * Constants::playerStrafe;
    if (i.strafeLeft)  position.x -= dt * Constants::playerStrafe;
    if (i.strafeRight) position.x += dt * Constants::playerStrafe;
}

void Y65535::Player::Shoot(float dt, Input const& i, Bullets& bullets) {
    tSinceShoot += dt;
    if (i.shoot && tSinceShoot > Constants::playerShootInterval) {
        bullets.Spawn(position, velocity, true);
        tSinceShoot = 0.0f;
    }
}

bool Y65535::Player::HarmNear(Sphere other, float damage) {
    if (Intersect(Bounds(), other)) {
        // TODO: Harm player.
        (void)damage;
        std::cout << "PLAYER HARMED\n";
        return true;
    } else {
        return false;
    }
}

glm::vec3 Y65535::Player::Position() const {
    return position;
}

glm::vec3 Y65535::Player::Velocity() const {
    return velocity;
}

Y65535::Sphere Y65535::Player::Bounds() const {
    return {position, Constants::playerRadius};
}
