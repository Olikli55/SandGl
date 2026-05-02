#ifndef SANDGL_WINDOW_H
#define SANDGL_WINDOW_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>




class Window
{
public:
     const unsigned int HEIGHT;
     const unsigned int WIDTH;
     GLFWwindow* window{};

     Window(int h, int w);
     ~Window();
     void init();
     void processInput() const;

     
private:
     void static framebuffer_size_callback (GLFWwindow* window,  int width,  int height);
     void static glfwErrorCallback(int error, const char* description);

};





#endif