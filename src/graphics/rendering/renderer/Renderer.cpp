#include "Renderer.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::ortho
#include <glm/gtc/type_ptr.hpp>         // glm::value_ptr


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


void Renderer::init(const Shader *shader_, const Shader* screenShader_)
{
    shader = shader_;
    screenShader = screenShader_;
    //generate all of the buffers
    //===========================//
    offsetVBO.init();
    screenVAO.init();
    screenVBO.init();
    vbo.init();
    vao.init();
    ebo.init();
    fbo.init();




    vertices = {
        1.0f, 1.0f,  // top-right
        1.0f, 0.0f,  // bottom-right
        0.0f, 0.0f,  // bottom-left
        0.0f, 1.0f   // top-left
    };
    indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };



    screenVAO.Bind();
    screenVBO.Bind();
    screenVBO.setBufferData(screenVertices , 24*sizeof(float));
    screenVAO.LinkAttribFloat(screenVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), nullptr);
    screenVAO.LinkAttribFloat(screenVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));




    vao.Bind();

    vbo.Bind();
    vbo.setBufferData(vertices.data(), vertices.size() * sizeof(float));  // Upload the vertices to the gpu


    const std::vector cellsTemp(GRID_H * GRID_W, 1u); // generate a list of ones
    offsetVBO.Bind();
    offsetVBO.setBufferData(cellsTemp.data(), cellsTemp.size() * sizeof(unsigned int)); // upload to the of each cell to the gpu


    ebo.Bind();
    ebo.setBufferData(indices.data(), indices.size() * sizeof(GLuint));




    vao.LinkAttribFloat(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), nullptr); //vertices
   // vao.LinkAttrib(vbo, 1, 3, GL_FLOAT,  sizeof(Vertex), reinterpret_cast<void*>(2 * sizeof(float))); //color
    vao.LinkAttribInt(offsetVBO, 1, 1, GL_UNSIGNED_INT,sizeof(unsigned int), nullptr); // type of each cell
    glVertexAttribDivisor(1,1);

    fbo.Bind();
    fbo.generateTexture(800,600);
    fbo.Unbind();


    glm::mat4 proj = glm::ortho(
        0.0f, GRID_W * cellSize,  // left, right
        GRID_H * cellSize, 0.0f,  //bottom, top  (this flips Y => top-left origin)
        -1.0f, 1.0f    //near, far
    );
    shader->use();
    shader->setData("uProj", glm::value_ptr(proj));
    shader->setData("uGridSize", GRID_W, GRID_H);
    shader->setData("uCellSize", cellSize, cellSize);
    shader->setData("uCamera", 0.0f, 0.0f);
}

void Renderer::allocateMem( size_t sizeV, size_t sizeI)
{
    vertices.reserve(sizeV + indices.size());
    indices.reserve(sizeI + indices.size());
}

void Renderer::DrawElements() const
{
    fbo.Bind();
    //glEnable(GL_DEPTH_TEST); // future proofing for 3D

    //clear every buffer
    glClearColor(0.2f, 0.2333f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    //bind the vertices and indices
    vao.Bind();
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr, GRID_H * GRID_W);


    //unbind to render the ui onto the default frame buffer
    fbo.Unbind();

}

void Renderer::onFramebufferResize(int width, int height){
    fbo.Bind();
    //delete the old texture
    if (fbo.textureColorBufferID != 0)
    {
        glDeleteTextures(1, &fbo.textureColorBufferID);
        fbo.textureColorBufferID = 0;
    }
    //generate the new one with the new H, W
    fbo.generateTexture(width, height);


    fbo.Unbind();


}


void Renderer::renderUi() const
{
    //glDisable(GL_DEPTH_TEST); // future proofing for 3D

    //clear buffers (stencil, depth, color, ...)
    glClearColor(0.2f, 0.2333f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //apply the screen shader
    screenShader->use();

    //bind the predefined vertices for the whole screen
    screenVAO.Bind();
    glBindTexture(GL_TEXTURE_2D, fbo.textureColorBufferID);
    //draw array
    glDrawArrays(GL_TRIANGLES, 0,6);
}

void Renderer::updateCells(const unsigned int* type){
    offsetVBO.Bind();
    offsetVBO.setBufferData(type, GRID_H * GRID_W * sizeof(unsigned int));
}

