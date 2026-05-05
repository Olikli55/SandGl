#ifndef SANDGL_FBO_H
#define SANDGL_FBO_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>


class FBO
{
public:
    unsigned int ID{};
    unsigned int textureColorBufferID{};
    FBO();
    void init();
    void generateTexture();
    void Delete() const;
    void Bind() const;
    void Unbind() const;
    void chekBufferForErr() const;
};


#endif //SANDGL_FBO_H
