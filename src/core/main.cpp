#include "shader.h"
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "generated_shaders.h"
#include "Renderer.h"

Shader shader(generated_shaders::default_vert, generated_shaders::default_frag);
Window window(800, 600);
Renderer renderer;
int main(){
    try{
        window.init();
        shader.init();
        renderer.init();
    }catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return -1;
    }



    //LOOP=====================================LOOP//
    while(!glfwWindowShouldClose(window.window))
    {
        glClearColor(0.2f, 0.2333f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        window.processInput();
        renderer.DrawElements();

        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }




    //END
    return 0;
}