#include <stdio.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utils.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0, vColor = 1 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

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
    window = glfwCreateWindow(512, 512, "Blend - OpenGL", NULL, NULL);
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
    glViewport(0, 0, 512, 512);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

bool blendenabled;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_UP:
            if (blendenabled) printf("Blend is already enabled.\n");
            else
            {
                glEnable(GL_BLEND);
                printf("Blend enabled.\n");
                blendenabled = true;
            }
            break;
        case GLFW_KEY_DOWN:
            if (!blendenabled) printf("Blend is already disabled.\n");
            else
            {
                glDisable(GL_BLEND);
                printf("Blend disabled.\n");
                blendenabled = false;
            }
            break;

        case GLFW_KEY_KP_1:
            glBlendEquation(GL_FUNC_ADD);
            printf("Blend equation switched to GL_FUNC_ADD");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_KP_2:
            glBlendEquation(GL_FUNC_SUBTRACT);
            printf("Blend equation switched to GL_FUNC_SUBTRACT");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_KP_3:
            glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
            printf("Blend equation switched to GL_FUNC_REVERSE_SUBTRACT");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_KP_4:
            glBlendEquation(GL_MIN);
            printf("Blend equation switched to GL_MIN");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_KP_5:
            glBlendEquation(GL_MAX);
            printf("Blend equation switched to GL_MAX");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;

        case GLFW_KEY_1:
            glBlendFunc(GL_ONE, GL_ZERO);
            printf("Blend function switched to GL_ONE, GL_ZERO");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_2:
            glBlendFunc(GL_ONE, GL_SRC_COLOR);
            printf("Blend function switched to GL_ONE, GL_SRC_COLOR");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_3:
            glBlendFunc(GL_ONE, GL_DST_COLOR);
            printf("Blend function switched to GL_ONE, GL_DST_COLOR");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_4:
            glBlendFunc(GL_ONE, GL_SRC_ALPHA);
            printf("Blend function switched to GL_ONE, GL_SRC_ALPHA");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_5:
            glBlendFunc(GL_ONE, GL_DST_ALPHA);
            printf("Blend function switched to GL_ONE, GL_DST_ALPHA");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_6:
            glBlendFunc(GL_ONE, GL_ONE_MINUS_DST_COLOR);
            printf("Blend function switched to GL_ONE, GL_ONE_MINUS_DST_COLOR");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_7:
            glBlendFunc(GL_ONE, GL_ONE_MINUS_DST_ALPHA);
            printf("Blend function switched to GL_ONE, GL_ONE_MINUS_DST_ALPHA");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_8:
            glBlendFunc(GL_SRC_COLOR, GL_DST_ALPHA);
            printf("Blend function switched to GL_SRC_COLOR, GL_DST_ALPHA");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        case GLFW_KEY_9:
            glBlendFunc(GL_ZERO, GL_DST_ALPHA);
            printf("Blend function switched to GL_ONE, GL_DST_ALPHA");
            printf(blendenabled ? ".\n" : ", but blend is currently disabled.\n");
            break;
        }
}

int main()
{
    CreateWindow(window);

    struct VertexData {
        GLfloat color[4];
        GLfloat position[4];
    };

    VertexData vertices[NumVertices] = {
        { { 1.00, 0.00, 0.00 ,0.5 }, { -0.70, -0.70 } },
        { { 0.00, 1.00, 0.00 ,0.5 }, {  0.70, -0.70 } },
        { { 1.00, 0.00, 0.00 ,0.5 }, {  0.00,  0.90 } },
        { { 0.00, 1.00, 0.00 ,0.5 }, {  0.00, -0.90 } },
        { { 0.00, 1.00, 0.00 ,0.5 }, {  0.70,  0.70 } },
        { { 0.00, 1.00, 0.00 ,0.5 }, { -0.70,  0.70 } }
    };

    unsigned int shaderProgram = loadShaders("blend.vert", "blend.frag");
    glUseProgram(shaderProgram);

    glGenVertexArrays(NumVAOs, VAOs);
    glGenBuffers(NumBuffers, Buffers);
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_TRUE, sizeof(VertexData), 0);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)sizeof(vertices[0].color));
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);

    glEnable(GL_BLEND);
    blendenabled = true;

    glfwSetKeyCallback(window, key_callback);

    printf("Tip: Press up/down to toggle on/off blend.\n");
    printf("     Press Ctrl + numpad 1-5 to switch between blend equations.\n");
    printf("     Press Ctrl + number 1-9 to switch between blend functions.\n\n");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(.0, .0, .0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
        glBindVertexArray(VAOs[Triangles]);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);

        glFlush();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
