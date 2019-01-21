#include "Bullets.hpp"

#include "../Assets.hpp"
#include "../Constants.hpp"
#include "../DrawContext.hpp"
#include "Enemies.hpp"
#include "Player.hpp"

void Y65535::Bullets::Step(float dt, Enemies& enemies, Player& player) {
    Age(dt);
    Travel(dt);
    TryCollideWithPlayer(player);
    TryCollideWithEnemies(enemies);
    RemoveDead();
}

void Y65535::Bullets::Age(float dt) {
    for (auto&& bullet : bullets) {
        bullet.age += dt;
    }
}

void Y65535::Bullets::Travel(float dt) {
    for (auto&& bullet : bullets) {
        bullet.position += dt * bullet.velocity;
    }
}

void Y65535::Bullets::TryCollideWithPlayer(Player& player) {
    for (auto&& bullet : bullets) {
        if (bullet.friendly) continue;
        bullet.collided += player.HarmNear(bullet.Bounds(),
                                           Constants::bulletDamage);
    }
}

void Y65535::Bullets::TryCollideWithEnemies(Enemies& enemies) {
    for (auto&& bullet : bullets) {
        if (!bullet.friendly) continue;
        bullet.collided += enemies.HarmNear(bullet.Bounds(),
                                            Constants::bulletDamage);
    }
}

void Y65535::Bullets::RemoveDead() {
    bullets.remove_if([&] (auto&& bullet) {
        return bullet.collided || bullet.age > Constants::maxBulletAge;
    });
}

void Y65535::Bullets::Spawn(glm::vec3 position, glm::vec3 vSource, bool friendly) {
    auto velocity = vSource + glm::normalize(vSource) * Constants::bulletSpeed;
    bullets.push_back({position, velocity, 0.0f, friendly, false});
}

void Y65535::Bullets::Draw(Assets const& a, DrawContext const& c) const {
    for (auto&& bullet : bullets) {
        auto m = bullet.Matrix();
        a.genericShader.Draw(a.bulletA, m, c.vp, c.lightPosition);
    }
}

Y65535::Sphere Y65535::Bullets::Bullet::Bounds() const {
    return {position, Constants::bulletRadius};
}

glm::quat Y65535::Bullets::Bullet::Rotation() const {
    return glm::quatLookAt(velocity, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Y65535::Bullets::Bullet::Matrix() const {
    return glm::translate(position) * glm::mat4(Rotation());
}
