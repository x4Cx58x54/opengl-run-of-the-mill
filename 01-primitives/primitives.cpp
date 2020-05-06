#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* window;
void CreateWindow(GLFWwindow*& window)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(800, 600, "Primitives - OpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window.\n");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD.\n");
        exit(-1);
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

int main()
{
    CreateWindow(window);
    unsigned int shaderProgram = loadShaders("vert.glsl", "frag.glsl");

    float vertices[] = {
        -0.24f, -0.13f, 0.0f, 1.0f, 1.0f, 1.0f, //  0

         0.91f,  0.06f, 0.0f, 1.0f, 1.0f, 1.0f, //  1

        -0.20f,  0.95f, 0.0f, 0.2f, 1.4f, 1.5f, //  2
         0.28f,  0.40f, 0.0f, 1.0f, 0.1f, 1.0f, //  3

        -0.85f, -0.84f, 0.0f, 0.9f, 0.9f, 0.0f, //  4
        -0.76f, -0.20f, 0.0f, 0.0f, 0.9f, 0.9f, //  5
        -0.58f, -0.65f, 0.0f, 0.9f, 0.0f, 0.9f, //  6
        -0.46f, -0.41f, 0.0f, 0.0f, 0.5f, 0.5f, //  7
        -0.17f, -0.48f, 0.0f, 1.0f, 1.0f, 0.8f, //  8

         0.20f, -0.40f, 0.0f, 1.0f, 0.3f, 0.2f, //  9
         0.36f, -0.95f, 0.0f, 0.2f, 0.6f, 1.0f, // 10
         0.76f, -0.77f, 0.0f, 0.7f, 1.0f, 0.5f, // 11
         0.59f, -0.27f, 0.0f, 0.9f, 0.9f, 0.3f, // 12

        -0.67f,  0.85f, 0.0f, 0.5f, 0.7f, 0.8f, // 13
        -0.91f,  0.24f, 0.0f, 0.8f, 0.5f, 0.7f, // 14
        -0.24f,  0.33f, 0.0f, 0.7f, 0.8f, 0.5f, // 15

         0.18f,  0.68f, 0.0f, 0.25f, 0.32f, 0.07f, // 16
         0.28f,  0.93f, 0.0f, 0.65f, 0.55f, 0.72f, // 17
         0.39f,  0.70f, 0.0f, 0.62f, 0.71f, 0.49f, // 18
         0.50f,  0.92f, 0.0f, 0.02f, 0.65f, 0.97f, // 19
         0.55f,  0.56f, 0.0f, 0.85f, 0.35f, 0.67f, // 20
         0.73f,  0.77f, 0.0f, 0.28f, 0.68f, 0.37f, // 21
         0.82f,  0.60f, 0.0f, 0.51f, 0.60f, 0.40f, // 22
         0.13f, -0.14f, 0.0f, 0.86f, 0.56f, 0.61f, // 23
         0.25f,  0.23f, 0.0f, 0.60f, 0.51f, 0.07f, // 24
         0.33f,  0.21f, 0.0f, 0.02f, 0.93f, 0.56f, // 25
         0.39f,  0.13f, 0.0f, 0.71f, 0.96f, 0.50f, // 26
         0.36f, -0.01f, 0.0f, 0.42f, 0.70f, 0.97f, // 27
         0.34f, -0.12f, 0.0f, 0.75f, 1.00f, 0.42f, // 28
    };

    unsigned int indices[] = {
        0,                          // point 1
        1,                          // point 2
        2, 3,                       // line
        4, 5, 6, 7, 8,              // line strip
        9, 10, 11, 12,              // line loop
        13, 14, 15,                 // trialgles
        16, 17, 18, 19, 20, 21, 22, // triangle strip
        23, 24, 25, 26, 27, 28,     // triangle fan
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.20f, 0.21f, 0.24f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, (void*)(0*sizeof(float)));
        glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, (void*)(1*sizeof(float)));
        glDrawElements(GL_LINES , 2, GL_UNSIGNED_INT, (void*)(2*sizeof(float)));
        glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(4*sizeof(float)));
        glDrawElements(GL_LINE_LOOP , 4, GL_UNSIGNED_INT, (void*)(9*sizeof(float)));
        glDrawElements(GL_TRIANGLES     , 3, GL_UNSIGNED_INT, (void*)(13*sizeof(float)));
        glDrawElements(GL_TRIANGLE_STRIP, 7, GL_UNSIGNED_INT, (void*)(16*sizeof(float)));
        glDrawElements(GL_TRIANGLE_FAN  , 6, GL_UNSIGNED_INT, (void*)(23*sizeof(float)));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
