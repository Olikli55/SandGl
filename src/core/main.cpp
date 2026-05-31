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
#include <thread>
#include <chrono>

Shader shader(generated_shaders::default_vert, generated_shaders::default_frag);
Shader screenShader(generated_shaders::screen_vert, generated_shaders::screen_frag);
Renderer renderer;
Grid gridManager;
Window window(800, 600, &screenShader, &renderer, &gridManager);
ImageTexture imageTexture;
float deltaTime = 0;
float lastTime = 0;
float timer = 0;
unsigned int temp = 0;
unsigned int tempy = 4;
constexpr double targetFPS = 60.0;
constexpr auto targetFrame = std::chrono::duration<double>(1.0 / targetFPS);
int main(){
    try{
        window.init();
        shader.init();
        screenShader.init();
        renderer.init(&shader, &screenShader);
        //imageTexture = ImageLoader::loadImage("../assets/textures/container.jpg"); //current path is "SandGl/cmake-build-debug" therefore i need to use the ..

    }catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return -1;
    }



    screenShader.use();
    if (const GLint loc = glGetUniformLocation(screenShader.ID, "screenTexture");
        loc != -1) {
        glUniform1i(loc, 0);
    }

    using clock = std::chrono::steady_clock;
    auto nextPresent = clock::now();              // time of next render
    auto lastPresent = clock::now();              // for render delta if you want it


    //LOOP=====================================LOOP//
    while(!glfwWindowShouldClose(window.window))
    {
        //time logic
        //==============//
        //const auto currentFrame = static_cast<float>(glfwGetTime());
        //deltaTime = currentFrame - lastTime;
        //lastTime = currentFrame;
        //timer += deltaTime;


        if (window.pressedOnce(GLFW_KEY_SPACE)){
            //gridManager.update();
        }
        gridManager.update();

        if (auto now = clock::now();
            now >= nextPresent)
        {
            //update the buffers with new data
            //=================================//
            renderer.updateCells(&gridManager.bufferGrid[0][0]);


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
        }


        //glfw - swap buffers and poll inpout + output events (keypress, mouse move ....);
        //================================================================================//
        glfwSwapBuffers(window.window);
        glfwPollEvents();



    }




    //END
    return 0;
}




