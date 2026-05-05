cmake_minimum_required(VERSION 4.2)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SandGl)

set(CMAKE_CXX_STANDARD 23)
set(OpenGL_GL_PREFERENCE GLVND)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# ---- Generate embedded shader header ----
set(SHADER_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/rendering/shader")
set(SHADER_OUTPUT_FILE "${SHADER_OUTPUT_DIR}/generated_shaders.h")

set(DEFAULT_VERT_SHADER "${CMAKE_CURRENT_SOURCE_DIR}/shaders/default.vert")
set(DEFAULT_FRAG_SHADER "${CMAKE_CURRENT_SOURCE_DIR}/shaders/default.frag")

set(SCREEN_VERT_SHADER "${CMAKE_CURRENT_SOURCE_DIR}/shaders/frameBufferShaders/frameBuffer.vert")
set(SCREEN_FRAG_SHADER "${CMAKE_CURRENT_SOURCE_DIR}/shaders/frameBufferShaders/frameBuffer.frag")

add_custom_command(
        OUTPUT ${SHADER_OUTPUT_FILE}
        COMMAND ${CMAKE_COMMAND}
        -DINPUT_VERT=${DEFAULT_VERT_SHADER}
        -DINPUT_FRAG=${DEFAULT_FRAG_SHADER}
        -DINPUT_SCREEN_VERT=${SCREEN_VERT_SHADER}
        -DINPUT_SCREEN_FRAG=${SCREEN_FRAG_SHADER}
        -DOUTPUT_FILE=${SHADER_OUTPUT_FILE}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/embed_shaders.cmake
        DEPENDS ${DEFAULT_VERT_SHADER} ${DEFAULT_FRAG_SHADER} ${SCREEN_VERT_SHADER} ${SCREEN_FRAG_SHADER}
        COMMENT "Generating embedded shader header"
        VERBATIM
)

add_custom_target(generate_shaders DEPENDS ${SHADER_OUTPUT_FILE})

add_executable(${PROJECT_NAME}
        ${SRC_FILES}
        include/glad/src/gl.c
        ${SHADER_OUTPUT_FILE}
)

add_dependencies(${PROJECT_NAME} generate_shaders)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/window/
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/rendering/buffers/
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/rendering/shader/
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/rendering/renderer/
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/ImageLoader/
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/include/stb_image/
        ${CMAKE_CURRENT_SOURCE_DIR}/src/util/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenGL::GL
        glfw
        ${CMAKE_DL_LIBS}
)