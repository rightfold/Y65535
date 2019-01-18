#pragma once

#include "../../Support/Gl.hpp"

namespace Y65535 {
    template<typename T>
    class VertexBuffer;

    /// The shader that is used for most drawing. This class provides an
    /// interface for setting the attributes and uniforms of the shader.
    class GenericShader {
    public:
        /// The shader uses a vertex buffer with such vertices in it.
        struct Vertex {
            glm::vec3 position;
            glm::vec3 normal;
        };

        GenericShader(GenericShader const&) = delete;
        GenericShader& operator=(GenericShader const&) = delete;

        /// Compile the shader and set up the vertex array.
        GenericShader();

        /// Draw vertices with this shader.
        void Draw(VertexBuffer<Vertex> const& vb,
                  glm::mat4 m, glm::mat4 vp,
                  glm::vec3 lightPosition) const;

    private:
        GLuint program;
        GLuint vertexArray;
    };
}
