#pragma once

#include "../../Support/Gl.hpp"

namespace Y65535 {
    class Bullets;
    class Input;

    /// The player.
    class Player {
    public:
        /// Initialize the player.
        Player();

        /// Simulate the player.
        /// @param bullets Used to spawn bullets.
        void Step(float dt, Input const& i, Bullets& bullets);

        /// Harm the player if it is near the given position.
        bool HarmNear(Sphere other, float damage);

        glm::vec3 Position() const;
        glm::vec3 Velocity() const;
        Sphere Bounds() const;

    private:
        void Look(Input const& i);
        void Travel(float dt, Input const& i);
        void Shoot(float dt, Input const& i, Bullets& bullets);

        glm::vec3 position;
        glm::vec3 velocity;

        float tSinceShoot;
    };
}
