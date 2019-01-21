#pragma once

#include "../../Support/Gl.hpp"

#include <list>

namespace Y65535 {
    class Assets;
    class DrawContext;
    class Player;

    /// Collection of junks. While "junk" is a mass noun, we pretend it isn't
    /// here, for convenience.
    class Junks {
    public:
        /// Simulate all junks.
        /// @param player Used to remove junk the player passed.
        void Step(float dt, Player const& player);

        /// Spawn a new junk.
        void Spawn(glm::vec3 position, glm::vec3 velocity);

        /// Draw all junks.
        void Draw(Assets const& a, DrawContext const& c) const;

    private:
        void Travel(float dt);
        void RemoveDead(Player const& player);

        struct Junk {
            glm::vec3 position;
            glm::vec3 velocity;

            glm::mat4 Matrix() const;
        };

        std::list<Junk> junks;
    };
}
