#pragma once

#include "Assets.hpp"
#include "Entity/Bombs.hpp"
#include "Entity/Bullets.hpp"
#include "Entity/Enemies.hpp"
#include "Entity/Junks.hpp"
#include "Entity/Player.hpp"

namespace Y65535 {
    class Input;

    /// Collection of all game state.
    class Game {
    public:
        /// Add random entities. This is temporary.
        Game();

        /// Simulate all entities.
        void Step(float dt, Input const& i);

        /// Set up the camera and draw all entities.
        void Draw(float w, float h) const;

        Assets assets;

        Bombs bombs;
        Bullets bullets;
        Enemies enemies;
        Junks junks;
        Player player;
    };
}
