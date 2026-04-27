cmake_minimum_required(VERSION 4.2)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SandGl)

set(CMAKE_CXX_STANDARD 23)
set(OpenGL_GL_PREFERENCE GLVND)


file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")

add_executable(${PROJECT_NAME}
        ${SRC_FILES}
        glad/src/gl.c
)
# Allow #include from the src directory
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src                  # For your code
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include  # For glad (#include <glad/glad.h>)
)


find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenGL::GL
        glfw
        ${CMAKE_DL_LIBS}
)

