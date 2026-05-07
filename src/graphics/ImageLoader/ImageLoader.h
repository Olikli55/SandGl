#ifndef SANDGL_IMAGELOADER_H
#define SANDGL_IMAGELOADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "ImageTexture.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>

class ImageLoader
{
    ImageLoader();
    ~ImageLoader();
public:
    static ImageTexture loadImage(const std::string& filePath);
    static void SetupRenderingTexture();
};


#endif //SANDGL_IMAGELOADER_H
