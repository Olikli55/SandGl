#include "Window.h"
#include <iostream>

Window::Window(const int h, const int w, const Shader* shader) : HEIGHT(h), WIDTH(w), shader(shader) //constructors
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

void Window::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPosX += 0.04f;
        shader->setData("x", static_cast<float>(cameraPosX));
        //std::cout << cameraPosX<< "\n";
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPosX -= 0.04f;
        shader->setData("x", static_cast<float>(cameraPosX));
        //std::cout << cameraPosX<< "\n ";

    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPosY += 0.04f;
        shader->setData("y", static_cast<float>(cameraPosY));
        //std::cout << cameraPosY<< "\n";

    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPosY -= 0.04f;
        shader->setData("y", static_cast<float>(cameraPosY));
        //std::cout << cameraPosY<< "\n";
    }
   // std::cout.flush();
}
