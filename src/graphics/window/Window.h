#ifndef SANDGL_WINDOW_H
#define SANDGL_WINDOW_H

#include  "shader.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <stdexcept>
#include <iostream>



class Window
{
public:
     const unsigned int HEIGHT;
     const unsigned int WIDTH;
     double cameraPosX = 0;
     double cameraPosY = 0;
     GLFWwindow* window{};
     const Shader* shader;
     Window(int h, int w, const Shader* shader);
     ~Window();
     void init();
     void processInput();

     
private:
     void static framebuffer_size_callback (GLFWwindow* window,  int width,  int height);
     void static glfwErrorCallback(int error, const char* description);

};





#endif