#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <iostream>

class Shader {
public:
    GLuint program;
    Shader(const GLchar* vertex_path, const GLchar* fragment_path);
    Shader(const GLchar* vertex_path, const GLchar* fragment_path, const GLchar* geometry_path);

    void use();

private:
    void createShader(const GLchar* path, GLuint& shader, GLenum shader_type);
    void createShaderProgram(GLuint shaders[], int shaders_count, GLuint& program);
    void checkShaderProgram(GLuint shader_program);
};

inline Shader::Shader(const GLchar* vertex_path, const GLchar* fragment_path, const GLchar* geometry_path) {
    GLuint vertex, fragment, geometry;
    createShader(vertex_path, vertex, GL_VERTEX_SHADER);
    createShader(fragment_path, fragment, GL_FRAGMENT_SHADER);
    createShader(geometry_path, geometry, GL_GEOMETRY_SHADER);
    createShaderProgram(new GLuint[3]{vertex, fragment, geometry}, 3, this->program);
    checkShaderProgram(this->program);
}

inline Shader::Shader(const GLchar* vertex_path, const GLchar* fragment_path) {
    GLuint vertex, fragment;
    createShader(vertex_path, vertex, GL_VERTEX_SHADER);
    createShader(fragment_path, fragment, GL_FRAGMENT_SHADER);
    createShaderProgram(new GLuint[2]{vertex, fragment}, 2, this->program);
    checkShaderProgram(this->program);
}

inline void Shader::use() {
    glUseProgram(this->program);
}

inline void Shader::createShaderProgram(GLuint shaders[], const int shaders_count, GLuint& program) {
    program = glCreateProgram();

    for (int i = 0; i < shaders_count; i++)
        glAttachShader(program, shaders[i]);

    glLinkProgram(program);
}

inline void Shader::createShader(const GLchar* path, GLuint& shader, const GLenum shader_type) {
    std::string code;
    try {
        std::ifstream file;
        file.open(path);
        std::stringstream shaderStream;
        shaderStream << file.rdbuf();
        file.close();
        code = shaderStream.str();
    } catch (const std::ifstream::failure& e) //TODO: warning
    {
        std::cout << "ERROR_SHADER_NOT_SUCCESSFULLY_READ" << '\n';
    }

    const GLchar* shaderCode = code.c_str();

    GLint success;

    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR_VERTEX_SHADER_COMPILE" << infoLog << '\n';
    }
}

inline void Shader::checkShaderProgram(const GLuint shader_program) {
    GLint success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shader_program, 512, 0, infoLog);
        std::cout << "ERROR_LINK_PROGRAM" << infoLog << '\n';
    }
}
