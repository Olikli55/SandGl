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
Shader screenShader(generated_shaders::screen_vert, generated_shaders::default_frag);
Renderer renderer;
Window window(800, 600, &shader);
ImageTexture imageTexture;
float deltaTime = 0;
float lastTime = 0;
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


    shader.use();
    screenShader.use();


    //@todo i think something is worng i dont see the line in the middle of the screen
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //LOOP=====================================LOOP//
    while(!glfwWindowShouldClose(window.window))
    {
        //time logic
        //==============//
        const auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastTime;
        lastTime = deltaTime;

        //proces input
        //============//
        window.processInput();




        glClearColor(0.2f, 0.2333f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindTexture(GL_TEXTURE_2D, imageTexture.ID);


        renderer.DrawElements();
        //@todo make this whole function commented and split it into smaller more understandable functions
        renderer.fbo.Unbind();
        glDisable(GL_DEPTH_TEST); // future proofing for 3D
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screenShader.use();
        glBindVertexArray(renderer.screenVAO.ID);
        glBindTexture(GL_TEXTURE_2D, renderer.fbo.textureColorBufferID);
        glDrawArrays(GL_TRIANGLES, 0,6);




        //glfw - swap buffers and poll inpout + output events (keypress, mouse move ...);
        //================================================================================//
        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }




    //END
    return 0;
}