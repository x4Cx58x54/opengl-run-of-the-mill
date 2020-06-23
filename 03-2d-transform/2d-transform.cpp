#include "utils.h"

const int NumVAOs = 2;
const int NumBuffers = 2;
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 3;

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
    window = glfwCreateWindow(800, 800, "2D Transform - OpenGL", NULL, NULL);
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

    GLfloat vertices[NumVertices][4] = {
        { 0.0, 0,   1, 1 },
        { 0.5, 0.0, 1, 1 },
        { 0.0, 0.5, 1, 1 }
    };
    static const GLfloat colors[]
    {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };
    static const GLfloat coord_verteces[4][4] = {
        {-1.0,  0.0, 1.0, 1.0 },
        { 1.0,  0.0, 1.0, 1.0 },
        { 0.0, -1.0, 1.0, 1.0 },
        { 0.0,  1.0, 1.0, 1.0 }
    };
    glGenVertexArrays(NumVAOs, VAOs);
    glGenBuffers(NumBuffers, Buffers);

    Shader shaderProgram = Shader("transform.vert", "triangle.frag");
    Shader axesShaderProgram = Shader("axes.vert", "axes.frag");
    shaderProgram.useProgram();

    glGenBuffers(NumBuffers, Buffers);
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    axesShaderProgram.useProgram();
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coord_verteces) , coord_verteces, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.useProgram();
        glBindVertexArray(VAOs[0]);
        glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
        glDrawArrays(GL_TRIANGLES, 0, NumVertices);
        axesShaderProgram.useProgram();
        glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_LINES, 0, 4);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
