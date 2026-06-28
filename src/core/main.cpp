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


    //LOOP=====================================LOOP//
    while(!glfwWindowShouldClose(window.window))
    {

        if (window.pressedOnce(GLFW_KEY_SPACE)){
            gridManager.update();
        }

        if (auto now = clock::now();
            now >= nextPresent)
        {
            gridManager.update();


            //update the buffers with new data
            //=================================//
            renderer.updateCells(static_cast<const uint8_t*>(static_cast<const void*>(&gridManager.grid[0][0])));


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



            nextPresent += std::chrono::duration_cast<clock::duration>(targetFrame);


            //vsync catchup
            //=============//
            if (now > nextPresent + 5 * targetFrame)
            {
                nextPresent = now + std::chrono::duration_cast<clock::duration>(targetFrame);
            }

        }






    }




    //END
    return 0;
}




