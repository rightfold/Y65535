#pragma once

#include "../Support/Gl.hpp"
#include "../Support/VertexBuffer.hpp"
#include "Assets/GenericShader.hpp"

namespace Y65535 {
    class Assets {
    public:
        Assets();

        GenericShader genericShader;
        VertexBuffer<GenericShader::Vertex> bulletA;
        VertexBuffer<GenericShader::Vertex> junkA;
        VertexBuffer<GenericShader::Vertex> enemyA;
    };
}
