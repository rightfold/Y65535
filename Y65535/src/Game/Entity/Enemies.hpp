#pragma once

#include "../../Support/Gl.hpp"

#include <list>

namespace Y65535 {
    class Assets;
    class Bullets;
    class DrawContext;
    class Explosions;
    class Player;

    /// Collection of enemies.
    class Enemies {
    public:
        /// Simulate all enemies.
        /// @param bullets Used to spawn bullets.
        /// @param explosions Used to spawn explosions.
        /// @param player Used to find the player position in order to shoot at
        ///               the player.
        void Step(float dt, Bullets& bullets, Explosions& explosions,
                  Player const& player);

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
        void SpawnExplosions(Explosions& explosions) const;
        void RemoveDead(Player const& player);

        struct Enemy {
            glm::vec3 position;
            glm::vec3 velocity;
            float health;
            float tSinceShoot;

            bool Alive() const;
            Sphere Bounds() const;
            glm::mat4 Matrix() const;
        };

        std::list<Enemy> enemies;
    };
}
