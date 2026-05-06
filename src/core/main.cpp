#include "shader.h"
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "generated_shaders.h"
#include "Renderer.h"
#include "ImageTexture.h"
#include "ImageLoader.h"

void checkGLErrors(const char* operation);


Shader shader(generated_shaders::default_vert, generated_shaders::default_frag);
Shader screenShader(generated_shaders::screen_vert, generated_shaders::screen_frag);
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
    checkGLErrors("after init classes");


    shader.use();    checkGLErrors("shader.use init");
    screenShader.use();    checkGLErrors("shader.use init");




    //LOOP=====================================LOOP//
    while(!glfwWindowShouldClose(window.window))
    {
        //time logic
        //==============//
        const auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;
        checkGLErrors("after delta");
        //proces input
        //============//
        window.processInput();



        //@todo make this whole function commented and split it into smaller more understandable functions
        renderer.fbo.Bind(); checkGLErrors("fbo.bind");
        //glEnable(GL_DEPTH_TEST); // future proofing for 3D

        glClearColor(0.2f, 0.2333f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use(); checkGLErrors("sahder.use");
        glBindTexture(GL_TEXTURE_2D, imageTexture.ID); checkGLErrors("glbindTexture");
        renderer.DrawElements(); checkGLErrors("draw elements");
        renderer.fbo.Unbind(); checkGLErrors("fbo.unbind");
        //glDisable(GL_DEPTH_TEST); // future proofing for 3D


        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screenShader.use(); checkGLErrors("screenshader.use");
        renderer.screenVAO.Bind();
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


void checkGLErrors(const char* operation) {
    GLenum error;
    bool hasError = false;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL Error after '" << operation << "': " << error << std::endl;
        hasError = true;
    }
    if (hasError) std::exit(-1);  // Halt on errors
}