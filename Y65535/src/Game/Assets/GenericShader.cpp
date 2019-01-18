#include "GenericShader.hpp"

#include "../../Support/VertexBuffer.hpp"

// TODO: Consider not leaking OpenGL objects.

namespace {
    GLchar const vshaderSource[] = {
        #include "GenericShader.vert.ipp"
    };

    GLchar const fshaderSource[] = {
        #include "GenericShader.frag.ipp"
    };
}

Y65535::GenericShader::GenericShader() {
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

void Y65535::GenericShader::Draw(VertexBuffer<Vertex> const& vb,
                                 glm::mat4 m, glm::mat4 vp,
                                 glm::vec3 lightPosition) const {
    glUseProgram(program);

    {
        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, vb.buffer);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*) 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
    }

    {
        glUniformMatrix4fv(0, 1, false, glm::value_ptr(m));
        glUniformMatrix4fv(1, 1, false, glm::value_ptr(vp));
        glUniform3fv(2, 1, glm::value_ptr(lightPosition));
    }

    glDrawArrays(GL_TRIANGLES, 0, vb.count);
}
