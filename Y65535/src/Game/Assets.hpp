#pragma once

#include "../Support/Gl.hpp"
#include "../Support/VertexBuffer.hpp"
#include "Assets/GenericShader.hpp"
#include "Assets/ParticleShader.hpp"

namespace Y65535 {
    class Assets {
    public:
        Assets();

        GenericShader genericShader;
        VertexBuffer<GenericShader::Vertex> bomb;
        VertexBuffer<GenericShader::Vertex> bulletA;
        VertexBuffer<GenericShader::Vertex> enemyA;
        VertexBuffer<GenericShader::Vertex> junkA;

        ParticleShader particleShader;
        VertexBuffer<ParticleShader::Vertex> explosionA;
    };
}
