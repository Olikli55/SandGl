#include "Window.h"
#include <iostream>

Window::Window(const int h, const int w, const Shader* shader,  Renderer* renderer_, Grid* gridManager) : height(h), width(w), shader(shader), renderer(renderer_), grid(gridManager) //constructors
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window pointer
    window = glfwCreateWindow(width, height, "SandGL", nullptr, nullptr);
    if (window == nullptr) // chek for correct window creation
    {
        throw std::runtime_error("failed to init glfw");
    }
    glfwMakeContextCurrent(window); // apply the window
    glfwSwapInterval(1); // 1 = vsync on

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("failed to load glad");
    }
    glViewport(0, 0, 800, 600);

    glfwSetWindowUserPointer(window, const_cast<Window*>(this));
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // set a function for resizing the window
    glfwSetCursorPosCallback(window, cursor_position_callback); // set a mouse pos callback
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}
//Input
//==========/

void Window::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

}

bool Window::pressedOnce(int key) const
{
    static bool prev[GLFW_KEY_LAST + 1] = {};

    const bool now  = glfwGetKey(window, key) == GLFW_PRESS;
    const bool once = now && !prev[key];

    prev[key] = now;
    return once;
}

//callbacks
//=============//

void Window::cursor_position_callback(GLFWwindow* window, double xPos, double yPos)
{

    if (auto* windowClass  = static_cast<Window*>(glfwGetWindowUserPointer(window))) {


        const auto winH = static_cast<double>(windowClass->height);
        const auto winW = static_cast<double>(windowClass->width);

        constexpr double worldH = Renderer::GRID_H * Renderer::cellSize;
        constexpr double worldW = Renderer::GRID_W * Renderer::cellSize;

        constexpr double camX = 0.0f;
        constexpr double camY = 0.0f; // future update

        const double worldX = (xPos/winW) * worldW - camX;
        const double worldY = (yPos/winH) * worldH - camY;

        const int cellX = static_cast<int>(worldX/Renderer::cellSize);
        const int cellY = static_cast<int>(worldY/Renderer::cellSize);
        windowClass->mousePosX = cellX;
        windowClass->mousePosY = cellY;
    }

}

void Window::glfwErrorCallback(const int error, const char* description) {
    throw std::runtime_error("GLFW err " + std::to_string(error) + ": " + description);
}

void Window::framebuffer_size_callback(GLFWwindow* window, const int _width, const int _height)
{
    if (auto* windowClass  = static_cast<Window*>(glfwGetWindowUserPointer(window))) {
        windowClass->renderer->onFramebufferResize(_width, _height);
        windowClass->height = _height;
        windowClass->width = _width;
    }

    glViewport(0, 0, _width, _height);


}
void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (auto* windowClass  = static_cast<Window*>(glfwGetWindowUserPointer(window))) {
            if (button == GLFW_MOUSE_BUTTON_LEFT){
                windowClass->grid->bufferGrid[windowClass->mousePosY][windowClass->mousePosX] = 2;

            }else if (button == GLFW_MOUSE_BUTTON_RIGHT){
                windowClass->grid->bufferGrid[windowClass->mousePosY][windowClass->mousePosX] = 1;

            }
        }
    }
}

