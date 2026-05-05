#include "FBO.h"



FBO::FBO()=default;

void FBO::init(){
    glGenBuffers(1, &ID);
}

void FBO::generateTexture()
{
    glGenBuffers(1, &textureColorBufferID);
    glBindBuffer(GL_TEXTURE_2D, textureColorBufferID);
    //@todo figure out how to get the current size bc this texture is suposed to cover the whole screen
    glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGB, 500,500,0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glBindTexture(GL_TEXTURE_2D, 0);


    //@todo implement RBO for depth and stencil
    // remember those cant be sampled
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBufferID, 0);
    chekBufferForErr();
    Unbind();
}

void FBO::Bind() const
{
    glBindBuffer(GL_FRAMEBUFFER, ID);
}

void FBO::Unbind() const
{
    glBindBuffer(GL_FRAMEBUFFER, 0);
}


void FBO::chekBufferForErr() const
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "FrameBuffer error (" << glCheckFramebufferStatus(GL_FRAMEBUFFER) << "):\n";
        throw std::runtime_error("Frame Buffer failed to complete ");
    }
}


void FBO::Delete() const
{
    glDeleteBuffers(1, &ID);
}
