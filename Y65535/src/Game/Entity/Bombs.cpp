#include "Bombs.hpp"

#include "../Assets.hpp"
#include "../DrawContext.hpp"
#include "Player.hpp"

void Y65535::Bombs::Step(Player const& player) {
    RemoveDead(player);
}

void Y65535::Bombs::RemoveDead(Player const& player) {
    bombs.remove_if([&] (auto&& bomb) {
        return bomb.position.z > player.Position().z;
    });
}

void Y65535::Bombs::Spawn(glm::vec3 position) {
    bombs.push_back({position});
}

void Y65535::Bombs::Draw(Assets const& a, DrawContext const& c) const {
    for (auto&& bomb : bombs) {
        auto m = bomb.Matrix();
        a.genericShader.Draw(a.bomb, m, c.vp, c.lightPosition);
    }
}

glm::mat4 Y65535::Bombs::Bomb::Matrix() const {
    return glm::translate(position);
}
