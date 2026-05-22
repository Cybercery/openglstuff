#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cmath>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    // Configure OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window =
        glfwCreateWindow(800, 600, "Concentric Triangles", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";

        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback
    );

    // Create shader
    Shader shader(
        "../../../shaders/basic.vert",
        "../../../shaders/basic.frag"
    );

    // Triangle vertices
    std::vector<float> vertices;

    int numTriangles = 7;

    float side = 1.6f;

    float spacing =
        side / (1.0f + (numTriangles - 1) * 2.0f * sqrt(3.0f));

    for (int i = 0; i < numTriangles; i++)
    {
        float h = side * sqrt(3.0f) / 2.0f;

        vertices.push_back(-side / 2);
        vertices.push_back(-h / 3);
        vertices.push_back(0.0f);

        vertices.push_back(side / 2);
        vertices.push_back(-h / 3);
        vertices.push_back(0.0f);

        vertices.push_back(0.0f);
        vertices.push_back(2 * h / 3);
        vertices.push_back(0.0f);

        side -= 2.0f * sqrt(3.0f) * spacing;
    }

    // VAO + VBO
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    // Vertex attribute
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    // Uniform location
    int colorLoc =
        glGetUniformLocation(shader.ID, "ourColor");

    // Rainbow colors
    float colors[7][4] =
    {
        {1,0,0,1},
        {1,0.5f,0,1},
        {1,1,0,1},
        {0,1,0,1},
        {0,0,1,1},
        {0.29f,0,0.51f,1},
        {0.56f,0,1,1}
    };

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        glBindVertexArray(VAO);

        for (int i = 0; i < numTriangles; i++)
        {
            float timeValue = glfwGetTime();

            float intensity =
                sin(timeValue - i * 0.6f) * 0.5f + 0.5f;

            float animatedColor[4] =
            {
                colors[i][0] * intensity,
                colors[i][1] * intensity,
                colors[i][2] * intensity,
                1.0f
            };

            glUniform4fv(colorLoc, 1, animatedColor);

            glDrawArrays(GL_TRIANGLES, i * 3, 3);
        }

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);

    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
}