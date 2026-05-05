#include "Renderer.h"



Renderer::Renderer() = default;

Renderer::~Renderer()
{
    vbo.Delete();
    ebo.Delete();
    vao.Delete();
    fbo.Delete();

    vertices.clear();
    indices.clear();
}


void Renderer::init()
{


    vertices = {
        // positions                          // colors           // texture coords
        {0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f}, // top right
        {0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f}, // bottom right
        {-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f}, // bottom left
        {-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f}  // top left
   };
    indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };


    allocateMem(100,200);

    screenVAO.init();
    screenVAO.Bind();

    screenVBO.init(screenVertices , 24*sizeof(float));



    //@todo i should change how binding and unbinding happens
    vao.init();
    vao.Bind();

    vbo.init(vertices.data(), vertices.size() * sizeof(Vertex));
    ebo.init(indices.data(), indices.size() * sizeof(GLuint));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), nullptr);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT,  sizeof(Vertex), reinterpret_cast<void*>(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT,  sizeof(Vertex), reinterpret_cast<void*>(6 * sizeof(float)));


    fbo.init();
    fbo.Bind();
    fbo.generateTexture();






}

void Renderer::allocateMem( size_t sizeV, size_t sizeI)
{
    vertices.reserve(sizeV + indices.size());
    indices.reserve(sizeI + indices.size());
}

void Renderer::DrawElements() const
{   fbo.Bind();
    vao.Bind();

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
}



