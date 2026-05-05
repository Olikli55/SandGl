#ifndef SANDGL_RBO_H
#define SANDGL_RBO_H
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>


class RBO
{
public:
    unsigned int ID{};
    RBO();
    void init();

    void Delete() const;
    void Bind() const;
    void Unbind() const;
};



#endif //SANDGL_RBO_H
