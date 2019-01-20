#include "Explosions.hpp"

#include "../Assets.hpp"
#include "../Constants.hpp"
#include "../DrawContext.hpp"

void Y65535::Explosions::Step(float dt) {
    Age(dt);
    RemoveDead();
}

void Y65535::Explosions::Age(float dt) {
    for (auto&& explosion : explosions) {
        explosion.age += dt;
    }
}

void Y65535::Explosions::RemoveDead() {
    explosions.remove_if([&] (auto&& explosion) {
        return explosion.age > Constants::maxExplosionAge;
    });
}

void Y65535::Explosions::Spawn(glm::vec3 position) {
    explosions.push_back({position, 0.0f});
}

void Y65535::Explosions::Draw(Assets const& a, DrawContext const& c) const {
    for (auto&& explosion : explosions) {
        auto scale = explosion.age * Constants::explosionScale;
        auto m = glm::translate(explosion.position) *
                 glm::scale(glm::vec3(scale));
        a.particleShader.Draw(a.explosionA, m, c.vp);
    }
}
