#include "Game.hpp"

#include "../Support/Gl.hpp"
#include "DrawContext.hpp"

#include <random>

Y65535::Game::Game() {
    std::random_device random;
    std::mt19937 rng(random());
    std::uniform_int_distribution<> dist(-3000, +1000);

    for (int i = 0; i < 8; ++i) {
        auto position = glm::vec3(dist(rng) / 6.0,
                                  dist(rng) / 6.0,
                                  dist(rng) - 1000.0);
        auto velocity = glm::vec3(dist(rng) / 1000.0,
                                  dist(rng) / 1000.0,
                                  dist(rng) / 1000.0);
        junks.Spawn(position, velocity);
    }

    for (int i = 0; i < 100; ++i) {
        auto position = glm::vec3(dist(rng) / 6.0,
                                  dist(rng) / 6.0,
                                  dist(rng) - 1000.0);
        enemies.Spawn(position);
    }
}

void Y65535::Game::Step(float dt, Input const& i) {
    bullets.Step(dt, enemies, player);
    enemies.Step(dt, bullets, player);
    junks.Step(dt, player);
    player.Step(dt, i, bullets);
}

void Y65535::Game::Draw(float w, float h) const {
    auto eye = player.Position();
    auto dir = player.Velocity();
    auto up  = glm::vec3(0.0f, 1.0f, 0.0f); // TODO: This should be the player roll.
    auto v = glm::lookAt(eye, eye + dir, up);
    auto p = glm::perspective(glm::radians(45.0f), w / h, 0.1f, 50000.0f);
    auto vp = p * v;

    DrawContext c;
    c.vp = vp;
    c.lightPosition = eye + glm::vec3(0.0f, 5.0f, 0.0f);

    bullets.Draw(assets, c);
    enemies.Draw(assets, c);
    junks.Draw(assets, c);
}
