#include <stdio.h>
#include <math.h>
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
    window = glfwCreateWindow(800, 800, "Primitive Restart and Projection - OpenGL", NULL, NULL);
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
    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

int main()
{
    CreateWindow(window);

    GLfloat vertices[8][4] = {
        { -0.2,  0.2,  0.2, 1 },
        { -0.2, -0.2,  0.2, 1 },
        {  0.2,  0.2,  0.2, 1 },
        {  0.2, -0.2,  0.2, 1 },
        {  0.2,  0.2, -0.2, 1 },
        {  0.2, -0.2, -0.2, 1 },
        { -0.2,  0.2, -0.2, 1 },
        { -0.2, -0.2, -0.2, 1 },
    };
    static const GLushort cube_indices[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 0, 1,
        0xffff,
        0, 2, 6, 4,
        0xffff,
        1, 7, 3, 5,
    };
    static const GLfloat colors[]{
        0.88, 0.35, 0.22, 1.0,
        0.83, 0.62, 0.29, 1.0,
        0.48, 0.88, 0.59, 1.0,
        0.46, 0.77, 0.83, 1.0,
        0.46, 0.77, 0.83, 1.0,
        0.48, 0.88, 0.59, 1.0,
        0.83, 0.62, 0.29, 1.0,
        0.88, 0.35, 0.22, 1.0,
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    unsigned int shaderProgram = loadShaders("transform.vert", "glsl.frag");
    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertices));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PRIMITIVE_RESTART_INDEX);
    glPrimitiveRestartIndex(0xffff);

    glOrtho(-1.5, 1.5, -1.5, 1.5, -10, 10);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(.0, .0, .0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawElements(GL_TRIANGLE_STRIP, sizeof(cube_indices), GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
