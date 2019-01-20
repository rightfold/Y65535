#pragma once

#include "../../Support/Gl.hpp"

namespace Y65535 {
    template<typename T>
    class VertexBuffer;

    /// The shader that is used for drawing particles. This class provides an
    /// interface for setting the attributes and uniforms of the shader.
    class ParticleShader {
    public:
        /// The shader uses a vertex buffer with such vertices in it.
        struct Vertex {
            glm::vec3 position;

            // TODO: Remove the normal vector as it is unused. This requires
            // TODO: alteration of ObjToCxx.pl as well.
            glm::vec3 normal;
        };

        ParticleShader(ParticleShader const&) = delete;
        ParticleShader& operator=(ParticleShader const&) = delete;

        /// Compile the shader and set up the vertex array.
        ParticleShader();

        /// Draw vertices with this shader.
        void Draw(VertexBuffer<Vertex> const& vb,
                  glm::mat4 m, glm::mat4 vp) const;

    private:
        GLuint program;
        GLuint vertexArray;
    };
}
