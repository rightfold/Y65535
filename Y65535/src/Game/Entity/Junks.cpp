#include "Junks.hpp"

#include "../Assets.hpp"
#include "../DrawContext.hpp"
#include "Player.hpp"

void Y65535::Junks::Step(float dt, Player const& player) {
    Travel(dt);
    RemoveDead(player);
}

void Y65535::Junks::Travel(float dt) {
    for (auto&& junk : junks) {
        junk.position += dt * junk.velocity;
    }
}

void Y65535::Junks::RemoveDead(Player const& player) {
    junks.remove_if([&] (auto&& junk) {
        return junk.position.z > player.Position().z;
    });
}

void Y65535::Junks::Spawn(glm::vec3 position, glm::vec3 velocity) {
    junks.push_back({position, velocity});
}

void Y65535::Junks::Draw(Assets const& a, DrawContext const& c) const {
    for (auto&& junk : junks) {
        auto m = glm::translate(junk.position);
        a.genericShader.Draw(a.junkA, m, c.vp, c.lightPosition);
    }
}
