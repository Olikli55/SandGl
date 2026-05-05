#include "shader.h"

#include <iostream>
#include <stdexcept>

Shader::Shader(const char* vertexSource, const char* fragmentSource)
    : m_vertexSource(vertexSource), m_fragmentSource(fragmentSource) {
}

Shader::~Shader() {
    if (ID != 0) {
        glDeleteProgram(ID);
    }
}

void Shader::init() {
    if (ID != 0) {
        glDeleteProgram(ID);
        ID = 0;
    }

    ID = CreateProgram(m_vertexSource, m_fragmentSource);
}

void Shader::use() const {
    glUseProgram(ID);
}

unsigned int Shader::CompileShader(unsigned int type, const char* source) {
    const unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    return shader;
}

unsigned int Shader::CreateProgram(const char* vertexSource, const char* fragmentSource) {
    const unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    CheckCompileErrors(vertexShader, "VERTEX");

    const unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    CheckCompileErrors(fragmentShader, "FRAGMENT");

    const unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    CheckCompileErrors(program, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Shader::CheckCompileErrors(unsigned int shader, const std::string& type) {
    int success = 0;
    char infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Shader compile error (" << type << "):\n" << infoLog << "\n";
            throw std::runtime_error("Shader compilation failed");
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Program link error:\n" << infoLog << "\n";
            throw std::runtime_error("Shader linking failed");
        }
    }
}


void Shader::setData(const std::string &varName, bool data) const
{
    glUniform1i(glGetUniformLocation(ID, varName.c_str()), static_cast<int>(data));
}
 void Shader::setData(const std::string &varName, float data)const
{
    glUniform1f(glGetUniformLocation(ID, varName.c_str()), data);
}
 void Shader::setData(const std::string &varName, int data)const
{
    glUniform1i(glGetUniformLocation(ID, varName.c_str()), data);
}
 void Shader::setData(const std::string &varName, double data)const
{
    glUniform1d(glGetUniformLocation(ID, varName.c_str()), data);
}