#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include "Window.h"

#include <stdexcept>
#include <iostream>

Window::Window(const int h, const int w) : HEIGHT(h), WIDTH(w) //constructors
{
    //empty :>
}

Window::~Window(){
    if (window){
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}


void Window::init()
{
    glfwSetErrorCallback(glfwErrorCallback); // set a error callback for handling errors
    if (!glfwInit()) //chek for correct initialization
    {
        throw std::runtime_error("failed to init glfw");

    }
    // set the version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window pointer
    window = glfwCreateWindow(WIDTH, HEIGHT, "SandGL", nullptr, nullptr);
    if (window == nullptr) // chek for correct window creation
    {
        throw std::runtime_error("failed to init glfw");
    }
    glfwMakeContextCurrent(window); // apply the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // set a function for resizing the window

    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("failed to load glad");
    }
    glViewport(0, 0, 800, 600);


}

void Window::glfwErrorCallback(const int error, const char* description) {
    throw std::runtime_error("GLFW err " + std::to_string(error) + ": " + description);
}

void Window::framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}

void Window::processInput() const
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
