#ifndef SANDGL_RENDERER_H
#define SANDGL_RENDERER_H

#include "VAO/VAO.h"
#include "VBO/VBO.h"
#include "EBO/EBO.h"
#include <vector>
#include <GLFW/glfw3.h>
#include "FBO/FBO.h"
#include "stb_image.h"
#include "shader.h"

class Renderer{

public:
    static constexpr int GRID_H =10;
    static constexpr int GRID_W =10;
    static constexpr float cellSize = 1.0f;

    Renderer();
    ~Renderer();
    void init(const Shader *shader, const Shader* screenShader);
    void allocateMem(size_t sizeV, size_t sizeI);
    void onFramebufferResize(int width, int height);
    void renderUi() const;
    const Shader* shader{};
    const Shader* screenShader{};
    void DrawElements() const;
    void updateCells(const unsigned int* type);
    std::vector<float> vertices{};
    std::vector<GLuint> indices{};
    float screenVertices[24] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };




private:
    VBO offsetVBO;

    VAO screenVAO;
    VBO screenVBO;
    FBO fbo;
    VAO vao;
    VBO vbo;
    EBO ebo;


    //EBO screenEBO;

};


#endif //SANDGL_RENDERER_H
