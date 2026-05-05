#ifndef SANDGL_RENDERER_H
#define SANDGL_RENDERER_H

#include "VAO/VAO.h"
#include "VBO/VBO.h"
#include "EBO/EBO.h"
#include <vector>
#include <GLFW/glfw3.h>
#include "vertex.h"
#include "FBO/FBO.h"
#include "stb_image.h"

class Renderer{

public:
    Renderer();
    ~Renderer();
    void init();
    void allocateMem(size_t sizeV, size_t sizeI);


    void DrawElements() const;
    std::vector<Vertex> vertices{};
    std::vector<GLuint> indices{};
    float screenVertices[24] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };



 //@todo temp
    VAO screenVAO;
    VBO screenVBO;
    FBO fbo;

private:

    VAO vao;
    VBO vbo;
    EBO ebo;


    //EBO screenEBO;

};


#endif //SANDGL_RENDERER_H
