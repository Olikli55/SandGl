#include "shader.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "generated_shaders.h"
#include "Renderer.h"
#include "ImageTexture.h"
#include "ImageLoader.h"


void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                             GLsizei length, const GLchar* message, const void* userParam);
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
        screenShader.init();
        renderer.init();
        imageTexture = ImageLoader::loadImage("../assets/textures/container.jpg"); //current path is "SandGl/cmake-build-debug" therefore i need to use the ..

    }catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return -1;
    }


    screenShader.use();
    GLint loc = glGetUniformLocation(screenShader.ID, "screenTexture");
    if (loc != -1) {
        glUniform1i(loc, 0);
    }
    // Enable debug output (OpenGL 4.3+)
    if (glDebugMessageCallback != nullptr) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        std::cout << "✓ OpenGL 4.6 Debug Mode Enabled" << std::endl;
    } else {
        std::cout << "⚠ OpenGL Debug Output not supported" << std::endl;
    }

    //LOOP=====================================LOOP//
    while(!glfwWindowShouldClose(window.window))
    {
        //time logic
        //==============//
        const auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;
        //proces input
        //============//
        window.processInput();



        //@todo make this whole function commented and split it into smaller more understandable functions
        renderer.fbo.Bind();
            //glEnable(GL_DEPTH_TEST); // future proofing for 3D

            glClearColor(0.2f, 0.2333f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.use();
            glBindTexture(GL_TEXTURE_2D, imageTexture.ID);
            renderer.DrawElements();
        renderer.fbo.Unbind();
        //glDisable(GL_DEPTH_TEST); // future proofing for 3D


        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screenShader.use();
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




void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                             GLsizei length, const GLchar* message, const void* userParam) {
    // Ignore some non-critical notifications
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::string sourceStr, typeStr, severityStr;

    // Source
    switch(source) {
        case GL_DEBUG_SOURCE_API: sourceStr = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: sourceStr = "WINDOW_SYSTEM"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "SHADER_COMPILER"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY: sourceStr = "THIRD_PARTY"; break;
        case GL_DEBUG_SOURCE_APPLICATION: sourceStr = "APPLICATION"; break;
        case GL_DEBUG_SOURCE_OTHER: sourceStr = "OTHER"; break;
        default: sourceStr = "UNKNOWN"; break;
    }

    // Type
    switch(type) {
        case GL_DEBUG_TYPE_ERROR: typeStr = "ERROR"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "DEPRECATED_BEHAVIOR"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: typeStr = "UNDEFINED_BEHAVIOR"; break;
        case GL_DEBUG_TYPE_PORTABILITY: typeStr = "PORTABILITY"; break;
        case GL_DEBUG_TYPE_PERFORMANCE: typeStr = "PERFORMANCE"; break;
        case GL_DEBUG_TYPE_MARKER: typeStr = "MARKER"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP: typeStr = "PUSH_GROUP"; break;
        case GL_DEBUG_TYPE_POP_GROUP: typeStr = "POP_GROUP"; break;
        case GL_DEBUG_TYPE_OTHER: typeStr = "OTHER"; break;
        default: typeStr = "UNKNOWN"; break;
    }

    // Severity
    switch(severity) {
        case GL_DEBUG_SEVERITY_HIGH: severityStr = "HIGH"; break;
        case GL_DEBUG_SEVERITY_MEDIUM: severityStr = "MEDIUM"; break;
        case GL_DEBUG_SEVERITY_LOW: severityStr = "LOW"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "NOTIFICATION"; break;
        default: severityStr = "UNKNOWN"; break;
    }

    std::cerr << "┌─ OpenGL Debug ─────────────────────\n"
              << "│ ID: " << id << "\n"
              << "│ Source: " << sourceStr << "\n"
              << "│ Type: " << typeStr << "\n"
              << "│ Severity: " << severityStr << "\n"
              << "│ Message: " << message << "\n"
              << "└────────────────────────────────────\n" << std::endl;

    if (type == GL_DEBUG_TYPE_ERROR) {
        std::exit(-1);  // Exit on errors
    }
}

void checkGLErrors(const char* operation) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::string errorStr;
        switch(error) {
            case GL_INVALID_ENUM: errorStr = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE: errorStr = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION: errorStr = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW: errorStr = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW: errorStr = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY: errorStr = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: errorStr = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default: errorStr = "UNKNOWN_ERROR"; break;
        }
        std::cerr << "❌ OpenGL Error after '" << operation << "': " << errorStr << " (0x"
                  << std::hex << error << std::dec << ")" << std::endl;
    }
}
