#pragma once

#include "../../Support/Gl.hpp"

#include <list>

namespace Y65535 {
    class Assets;
    class DrawContext;

    /// Collection of explosions.
    class Explosions {
    public:
        /// Simulate all explosions.
        void Step(float dt);

        /// Spawn a new explosion.
        void Spawn(glm::vec3 position);

        /// Draw all explosions.
        void Draw(Assets const& a, DrawContext const& c) const;

    private:
        void Age(float dt);
        void RemoveDead();

        struct Explosion {
            glm::vec3 position;
            float age;

            glm::mat4 Matrix() const;
        };

        std::list<Explosion> explosions;
    };
}
