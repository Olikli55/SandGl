//
// Created by plutonium on 5/1/26.
//

#include "Renderer.h"



Renderer::Renderer() = default;

Renderer::~Renderer()
{
    vbo.Delete();
    ebo.Delete();
    vao.Delete();

    vertices.clear();
    indices.clear();
}


void Renderer::init()
{


    vertices = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left
        };
    indices = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
        };

    allocateMem(100,200);

    vao.init();
    vao.Bind();

    vbo.init(vertices.data(), vertices.size() * sizeof(GLfloat));
    ebo.init(indices.data(), indices.size() * sizeof(GLuint));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), nullptr);
    //void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, const void* offset);

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();


}

void Renderer::allocateMem( size_t sizeV, size_t sizeI)
{
    vertices.reserve(sizeV + indices.size());
    indices.reserve(sizeI + indices.size());
}

void Renderer::DrawElements() const
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
}

