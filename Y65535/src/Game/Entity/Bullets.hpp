#pragma once

#include "../../Support/Gl.hpp"

#include <list>

namespace Y65535 {
    class Assets;
    class DrawContext;
    class Enemies;
    class Player;

    /// Collection of bullets.
    class Bullets {
    public:
        /// Simulate all bullets.
        /// @param enemies Used to harm the enemies when they are hit.
        /// @param player Used to harm the player when it is hit.
        void Step(float dt, Enemies& enemies, Player& player);

        /// Spawn a new bullet.
        /// @param vSource The velocity of the shooter.
        void Spawn(glm::vec3 position, glm::vec3 vSource, bool friendly);

        /// Draw all bullets.
        void Draw(Assets const& a, DrawContext const& c) const;

    private:
        void Age(float dt);
        void Travel(float dt);
        void TryCollideWithPlayer(Player& player);
        void TryCollideWithEnemies(Enemies& enemies);
        void RemoveDead();

        struct Bullet {
            glm::vec3 position;
            glm::vec3 velocity;
            float age;
            bool friendly;
            bool collided;

            Sphere Bounds() const;
            glm::quat Rotation() const;
            glm::mat4 Matrix() const;
        };

        std::list<Bullet> bullets;
    };
}
