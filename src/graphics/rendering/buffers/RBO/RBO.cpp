#include "RBO/RBO.h"

//INCOMPLETE
RBO::RBO()=default;

void RBO::init(){
    glGenBuffers(1, &ID);
}


void RBO::Bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, ID);
}

void RBO::Unbind() const
{
    glBindBuffer(GL_FRAMEBUFFER, 0);
}
