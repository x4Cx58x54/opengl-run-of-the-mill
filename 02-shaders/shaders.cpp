#include <stdio.h>
#include <math.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils.h"

const float pi = acos(-1);
enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLint Mode_View_Loc;
GLint Mode_Size_loc;
GLfloat Mode_Size = 10.0 / 10.0;
GLuint Render_Mode_loc;
GLuint Render_Mode = 0;
GLuint Polygon_sides = 4;
GLuint NumVertices = Polygon_sides + 2;
const GLuint Max_Polygon_sides = 64;
const GLuint Max_Render_Mode = 6;
GLfloat vertices[Max_Polygon_sides+3][2] = {
    {    0,    0 },
    {    0,  0.8 },
    { -0.8,    0 },
    {    0, -0.8 },
    {  0.8,    0 },
    {    0,  0.8 },
};
void polygon(int sides)
{
    float r = 0.8;
    float angle = 2*pi/sides;
    float x = 0, y = r;
    vertices[sides+1][0] = x;
    vertices[sides+1][1] = y;
    for(int i = 2; i <= sides; ++i)
    {
        vertices[i][0] = cos(angle)*x - sin(angle)*y;
        vertices[i][1] = cos(angle)*y + sin(angle)*x;
        x = vertices[i][0];
        y = vertices[i][1];
    }
    NumVertices = sides + 2;
}
void renewBuffer()
{
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);
    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(vPosition);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_L:
        case GLFW_KEY_RIGHT:
            if (Render_Mode < Max_Render_Mode)
                ++Render_Mode;
            else
                Render_Mode = 0;
            glUniform1ui(Render_Mode_loc, Render_Mode);
            printf("Render_Mode: %d\n", Render_Mode);
            break;
        case GLFW_KEY_H:
        case GLFW_KEY_LEFT:
            if (Render_Mode > 0)
                --Render_Mode;
            else
                Render_Mode = Max_Render_Mode;
            glUniform1ui(Render_Mode_loc, Render_Mode);
            printf("Render_Mode: %d\n", Render_Mode);
            break;
        case GLFW_KEY_K:
        case GLFW_KEY_UP:
            if (Polygon_sides < Max_Polygon_sides)
                ++Polygon_sides;
            else
                Polygon_sides = 3;
            polygon(Polygon_sides);
            printf("Polygon_sides: %d\n", Polygon_sides);
            break;
        case GLFW_KEY_J:
        case GLFW_KEY_DOWN:
            if (Polygon_sides > 3)
                --Polygon_sides;
            else
                Polygon_sides = Max_Polygon_sides;
            polygon(Polygon_sides);
            printf("Polygon_sides: %d\n", Polygon_sides);
            break;
        }
}
int main()
{
    printf("Tip: Press up/down to increase polygon sides, left/right to switch render mode.\n\n");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 800, "Shaders - OpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD.\n");
        return -1;
    }
    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    GLuint program = loadShaders("GLSL.vert", "GLSL.frag");
    glUseProgram(program);
    renewBuffer();
    Mode_View_Loc = glGetUniformLocation(program, "ModeColor");
    Mode_Size_loc = glGetUniformLocation(program, "size");
    Render_Mode_loc = glGetUniformLocation(program, "render_type");
    glUniform1f(Mode_View_Loc, -1.0f);
    glUniform1f(Mode_Size_loc, Mode_Size);
    while(!glfwWindowShouldClose(window))
    {
        renewBuffer();
        glClearColor(0.2f, 0.6f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAOs[VAO_IDs::Triangles]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, NumVertices);
        glFlush();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
