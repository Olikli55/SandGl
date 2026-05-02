#ifndef SANDGL_RENDERER_H
#define SANDGL_RENDERER_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <vector>
#include <GLFW/glfw3.h>


class Renderer{

public:
    Renderer();
    ~Renderer();
    void init();
    void allocateMem(size_t sizeV, size_t sizeI);


    void DrawElements() const;
    std::vector<GLfloat> vertices{};
    std::vector<GLuint> indices{};
private:


    VAO vao;
    VBO vbo;
    EBO ebo;

};


#endif //SANDGL_RENDERER_H
