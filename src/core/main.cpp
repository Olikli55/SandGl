#include "shader.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "generated_shaders.h"
#include "Renderer.h"
#include "ImageTexture.h"
#include "ImageLoader.h"
#include "Grid.h"

Shader shader(generated_shaders::default_vert, generated_shaders::default_frag);
Shader screenShader(generated_shaders::screen_vert, generated_shaders::screen_frag);
Renderer renderer;
Window window(800, 600, &screenShader, &renderer);
ImageTexture imageTexture;
Grid gridManager;
float deltaTime = 0;
float lastTime = 0;
float timer = 0;
unsigned int temp = 0;
unsigned int tempy = 4;
int main(){
    try{
        //grid.init();
        window.init();
        shader.init();
        screenShader.init();
        renderer.init(&shader, &screenShader);
        imageTexture = ImageLoader::loadImage("../assets/textures/container.jpg"); //current path is "SandGl/cmake-build-debug" therefore i need to use the ..

    }catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return -1;
    }



    screenShader.use();
    if (const GLint loc = glGetUniformLocation(screenShader.ID, "screenTexture");
        loc != -1) {
        glUniform1i(loc, 0);
    }


    //LOOP=====================================LOOP//
    while(!glfwWindowShouldClose(window.window))
    {
        //time logic
        //==============//
        const auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;
        timer += deltaTime;


        if (window.pressedOnce(GLFW_KEY_SPACE))
        {
            gridManager.update();
        }
//        gridManager.update();


        renderer.updateCells(&gridManager.grid[0][0]);


        //draw elements into FBO
        //======================//

        glBindTexture(GL_TEXTURE_2D, imageTexture.ID);
        renderer.DrawElements();


        //proces input
        //============//
        window.processInput();

        //render the FBO on top of everything
        //===================================//
        renderer.renderUi();

        //glfw - swap buffers and poll inpout + output events (keypress, mouse move ....);
        //================================================================================//
        glfwSwapBuffers(window.window);
        glfwPollEvents();



    }




    //END
    return 0;
}




