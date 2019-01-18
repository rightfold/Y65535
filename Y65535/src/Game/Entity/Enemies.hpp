#pragma once

#include "../../Support/Gl.hpp"

#include <list>

namespace Y65535 {
    class Assets;
    class Bullets;
    class DrawContext;
    class Player;

    /// Collection of enemies.
    class Enemies {
    public:
        /// Simulate all enemies.
        /// @param player Used to find the player position in order to shoot at
        ///               the player.
        /// @param bullets Used to spawn bullets.
        void Step(float dt, Bullets& bullets, Player const& player);

        /// Spawn a new enemy.
        void Spawn(glm::vec3 position);

        /// Harm the enemies that are near the given position.
        int HarmNear(Sphere other, float damage);

        /// Draw all enemies.
        void Draw(Assets const& a, DrawContext const& c) const;

    private:
        void SeekTarget(Player const& player);
        void Travel(float dt);
        void Shoot(float dt, Bullets& bullets);
        void RemoveDead(Player const& player);

        struct Enemy {
            glm::vec3 position;
            glm::vec3 velocity;
            float health;
            float tSinceShoot;

            Sphere Bounds() const;
        };

        std::list<Enemy> enemies;
    };
}