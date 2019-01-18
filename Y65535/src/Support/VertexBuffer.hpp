#pragma once

#include "Gl.hpp"

#include <cstddef>
#include <vector>

// TODO: Consider not leaking OpenGL objects.

namespace Y65535 {
    template<typename T>
    class VertexBuffer {
    public:
        VertexBuffer(VertexBuffer const&) = delete;
        VertexBuffer& operator=(VertexBuffer const&) = delete;

        using Vertex = T;

        explicit VertexBuffer(std::vector<Vertex> const& vertices) {
            glGenBuffers(1, &buffer);

            glBindBuffer(GL_ARRAY_BUFFER, buffer);

            auto bufferSize = vertices.size() * sizeof(Vertex);
            glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices.data(),
                         GL_STATIC_DRAW);

            count = vertices.size();
        }

        GLuint buffer;
        std::size_t count;
    };
}
