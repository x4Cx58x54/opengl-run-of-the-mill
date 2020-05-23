#include <stdio.h>
#include <math.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils.h"

enum VAO_IDs { Triangles, NumVAOs = 3 };
enum Buffer_IDs { ArrayBuffer, NumBuffers = 3 };
enum Attrib_IDs { vPosition };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint EBOs[2];
const GLuint NumVertices = 4;

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
    window = glfwCreateWindow(800, 800, "3D Transform - OpenGL", NULL, NULL);
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

    float v_p = 0.4 * sqrtf(3.0) / 2.0;
    GLfloat vertices[NumVertices][4] = {
        { 0.0, 0.0, -0.4,   1 },
        { 0.0, 0.56, 0.0,   1 },
        { v_p, 0.0,  0.4/2, 1 },
        {-v_p, 0.0,  0.4/2, 1 },
    };
    static const GLushort tetrahedron_indices[] =
        { 0, 1, 2, 2, 3, 0, 2, 1, 3, 0, 3, 1 };
    static const GLfloat colors[]{
        0.46, 0.77, 0.83, 1.0,
        0.48, 0.88, 0.59, 1.0,
        0.93, 0.62, 0.29, 1.0,
        0.97, 0.35, 0.22, 1.0,
    };
    static const GLushort edge_indices[] =
        { 0, 1, 0, 2, 0, 3, 1, 2, 1, 3, 2, 3 };
    static const GLfloat edge_colors[]{
        0.99, 0.00, 0.99, 1.0,
        0.99, 0.78, 0.00, 1.0,
        0.35, 0.77, 0.61, 1.0,
        0.49, 0.66, 0.80, 1.0,
    };
    static const GLfloat coord_vertices[][4] = {
        { 0.0, 0.0,  0.0, 1.0 },
        { 1.0, 0.0,  0.0, 1.0 },
        { 0.0, 0.0,  0.0, 1.0 },
        { 0.0, 1.0,  0.0, 1.0 },
        { 0.0, 0.0,  0.0, 1.0 },
        { 0.0, 0.0, -1.0, 1.0 },
    };
    static const GLfloat coord_colors[]{
        1.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
    };
    glGenVertexArrays(NumVAOs, VAOs);
    glGenBuffers(NumBuffers, Buffers);
    glGenBuffers(NumBuffers, Buffers);
    glGenBuffers(2, EBOs);
    unsigned int shaderProgram = loadShaders("transform.vert", "tetrahedron.frag");
    unsigned int axesShaderProgram = loadShaders("axes.vert", "axes.frag");

    glUseProgram(shaderProgram);
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tetrahedron_indices), tetrahedron_indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertices));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(edge_indices), edge_indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(edge_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(edge_colors), edge_colors);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertices));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glUseProgram(axesShaderProgram);
    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coord_vertices) + sizeof(coord_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(coord_vertices), coord_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(coord_vertices), sizeof(coord_colors), coord_colors);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(coord_vertices));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glDisable(GL_DEPTH_TEST);
        glClearColor(.0, .0, .0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)(3 * sizeof(GLushort)));
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)(6 * sizeof(GLushort)));
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)(9 * sizeof(GLushort)));

        glLineWidth(4);
        glBindVertexArray(VAOs[1]);
        glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, 0);
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, (void*)(2 * sizeof(GLushort)));
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, (void*)(4 * sizeof(GLushort)));
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, (void*)(6 * sizeof(GLushort)));
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, (void*)(8 * sizeof(GLushort)));
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, (void*)(10 * sizeof(GLushort)));

        glLineWidth(5);
        glUseProgram(axesShaderProgram);
        glBindVertexArray(VAOs[2]);
        glBindBuffer(GL_ARRAY_BUFFER, Buffers[2]);
        glDrawArrays(GL_LINES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
