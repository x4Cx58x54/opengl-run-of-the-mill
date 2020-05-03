#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

std::string readFile(const char* filename)
{
    std::ifstream f(filename);
    if (!f)
    {
        fprintf(stderr, "Fatal: File \"%s\" not found!\n", filename);
        exit(-1);
    }
    std::stringstream buffer;
    buffer << f.rdbuf();
    f.close();
    return buffer.str();
}

unsigned int loadShaders(const char * vShaderPath, const char * sShaderPath)
{
    std::string vShader = readFile(vShaderPath);
    std::string sShader = readFile(sShaderPath);
    const char* vShaderCode = vShader.c_str();
    const char * fShaderCode = sShader.c_str();
    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    int success;
    char errorlog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, errorlog);
        printf("Error: Vertex shader compile failed:\n%s\n", errorlog);
    }
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, errorlog);
        printf("Error: Fragment shader compile failed:\n%s\n", errorlog);
    }
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return shaderProgram;
}
