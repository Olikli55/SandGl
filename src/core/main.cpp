#include "shader.h"
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "generated_shaders.h"
#include "Renderer.h"
#include "ImageTexture.h"
#include "ImageLoader.h"

Shader shader(generated_shaders::default_vert, generated_shaders::default_frag);
Renderer renderer;
Window window(800, 600, &shader);
ImageTexture imageTexture;
int main(){
    try{
        window.init();
        shader.init();
        renderer.init();
        imageTexture = ImageLoader::loadImage("../assets/textures/container.jpg"); //current path is "SandGl/cmake-build-debug" therefore i need to use the ..

    }catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return -1;
    }

    //LOOP=====================================LOOP//
    while(!glfwWindowShouldClose(window.window))
    {
        glClearColor(0.2f, 0.2333f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glBindTexture(GL_TEXTURE_2D, imageTexture.ID);
        shader.use();


        window.processInput();
        renderer.DrawElements();

        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }




    //END
    return 0;
}