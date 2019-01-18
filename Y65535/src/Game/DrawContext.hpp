#pragma once

#include "../Support/Gl.hpp"

namespace Y65535 {
    // The draw context contains drawing information that is useful everywhere.
    class DrawContext {
    public:
        glm::mat4 vp;
        glm::vec3 lightPosition;
    };
}
