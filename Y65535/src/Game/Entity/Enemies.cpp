#include "Enemies.hpp"

#include "../Assets.hpp"
#include "../Constants.hpp"
#include "../DrawContext.hpp"
#include "Bullets.hpp"
#include "Player.hpp"

void Y65535::Enemies::Step(float dt, Bullets& bullets, Player const& player) {
    SeekTarget(player);
    Travel(dt);
    Shoot(dt, bullets);
    RemoveDead(player);
}

void Y65535::Enemies::SeekTarget(Player const& player) {
    // TODO: This should be more realistic than just pointing directly at the
    // TODO: player; there should be actual smooth rotation, and the enemies
    // TODO: should not always hit the player.

    for (auto&& enemy : enemies) {
        if (enemy.position.z > player.Position().z) {
            // TODO: We should despawn the enemy (in a separate method called
            // TODO: from Step) when it passes the player.
            continue;
        }

        auto vector = player.Position() - enemy.position;
        enemy.velocity = glm::normalize(vector) * Constants::enemySpeed;
    }
}

void Y65535::Enemies::Travel(float dt) {
    for (auto&& enemy : enemies) {
        enemy.position += dt * enemy.velocity;
    }
}

void Y65535::Enemies::Shoot(float dt, Bullets& bullets) {
    for (auto&& enemy : enemies) {
        enemy.tSinceShoot += dt;
        if (enemy.tSinceShoot > Constants::enemyShootInterval) {
            bullets.Spawn(enemy.position, enemy.velocity, false);
            enemy.tSinceShoot = 0.0f;
        }
    }
}

void Y65535::Enemies::Spawn(glm::vec3 position) {
    enemies.push_back({position, glm::vec3(0.0f),
                       Constants::enemyInitialHealth, 0.0f});
}

int Y65535::Enemies::HarmNear(Sphere other, float damage) {
    int n = 0;
    for (auto&& enemy : enemies) {
        if (Intersect(enemy.Bounds(), other)) {
            enemy.health -= damage;
            ++n;
        }
    }
    return n;
}

void Y65535::Enemies::RemoveDead(Player const& player) {
    enemies.remove_if([&] (auto&& enemy) {
        return enemy.health < 0.0f || enemy.position.z > player.Position().z;
    });
}

void Y65535::Enemies::Draw(Assets const& a, DrawContext const& c) const {
    for (auto&& enemy : enemies) {
        auto m = glm::translate(enemy.position);
        a.genericShader.Draw(a.enemyA, m, c.vp, c.lightPosition);
    }
}

Y65535::Sphere Y65535::Enemies::Enemy::Bounds() const {
    return {position, Constants::enemyRadius};
}
