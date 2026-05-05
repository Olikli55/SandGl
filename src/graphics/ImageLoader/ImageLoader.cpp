#include "ImageLoader.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ImageLoader::ImageLoader() = default;

ImageLoader::~ImageLoader() = default;

ImageTexture ImageLoader::loadImage(const std::string& filePath)
{
    ImageTexture image;
    unsigned char* imageData = nullptr;
    int channels = 0;

    glGenTextures(1, &image.ID);
    glBindTexture(GL_TEXTURE_2D, image.ID);// all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    //set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // set texture warping method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //https://learnopengl.com/Getting-started/Textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // what typo of filter to use when scaling up and..
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);               // when scaling down

    imageData = stbi_load(filePath.c_str(), &image.width, &image.height, &channels,0);
   // std::cout << std::filesystem::current_path() << std::endl;

    if (!imageData){
        stbi_image_free(imageData);
        throw std::runtime_error("failed to load image");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width , image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imageData);
    return image;
}


