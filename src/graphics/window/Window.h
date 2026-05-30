#ifndef SANDGL_WINDOW_H
#define SANDGL_WINDOW_H

#include  "shader.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <stdexcept>
#include <iostream>
#include "Grid.h"


class Window
{
public:
     int mousePosX{}, mousePosY{};
     unsigned int height;
     unsigned int width;
     double cameraPosX = 0;
     double cameraPosY = 0;
     GLFWwindow* window{};
     const Shader* shader;
     Grid* grid;
     Renderer* renderer;
     Window(int h, int w, const Shader* shader, Renderer* renderer_, Grid* grid);
     ~Window();
     void init();
     void processInput();
     bool pressedOnce(int key) const;

     
private:
     void static framebuffer_size_callback (GLFWwindow* window,  int width,  int height);
     void static glfwErrorCallback(int error, const char* description);
     void static cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
     void static mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

};





#endif