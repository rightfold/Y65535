#include "ParticleShader.hpp"

#include "../../Support/VertexBuffer.hpp"

// TODO: Consider not leaking OpenGL objects.

namespace {
    GLchar const vshaderSource[] = {
        #include "ParticleShader.vert.ipp"
    };

    GLchar const fshaderSource[] = {
        #include "ParticleShader.frag.ipp"
    };
}

Y65535::ParticleShader::ParticleShader() {
    ////////////////////////////////////
    // Program

    program = glCreateProgram();

    auto vshader = glCreateShader(GL_VERTEX_SHADER);
    auto fshader = glCreateShader(GL_FRAGMENT_SHADER);

    auto vshaderSourceP = vshaderSource;
    auto fshaderSourceP = fshaderSource;
    glShaderSource(vshader, 1, &vshaderSourceP, nullptr);
    glShaderSource(fshader, 1, &fshaderSourceP, nullptr);

    glCompileShader(vshader);
    glCompileShader(fshader);

    glAttachShader(program, vshader);
    glAttachShader(program, fshader);

    glLinkProgram(program);

    ////////////////////////////////////
    // Vertex array

    glGenVertexArrays(1, &vertexArray);
}

void Y65535::ParticleShader::Draw(VertexBuffer<Vertex> const& vb,
                                 glm::mat4 m, glm::mat4 vp) const {
    glUseProgram(program);

    {
        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, vb.buffer);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*) 0);
    }

    {
        glUniformMatrix4fv(0, 1, false, glm::value_ptr(m));
        glUniformMatrix4fv(1, 1, false, glm::value_ptr(vp));
    }

    glPointSize(5);
    glDrawArrays(GL_POINTS, 0, vb.count);
}
