#pragma once

#include "../../Support/Gl.hpp"

#include <list>

namespace Y65535 {
    class Assets;
    class DrawContext;
    class Player;

    /// Collection of bombs.
    class Bombs {
    public:
        /// Simulate all bombs.
        /// @param player Used to remove bomb the player passed.
        void Step(Player const& player);

        /// Spawn a new bomb.
        void Spawn(glm::vec3 position);

        /// Draw all bombs.
        void Draw(Assets const& a, DrawContext const& c) const;

    private:
        void RemoveDead(Player const& player);

        struct Bomb {
            glm::vec3 position;
        };

        std::list<Bomb> bombs;
    };
}
