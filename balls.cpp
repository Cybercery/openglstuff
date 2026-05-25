#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




float mixValue = 0.2f;

// view
glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

// Resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // up arrow increases mix value
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        // mix is between 0.0 and 1.0
        mixValue += 0.01f;
        if (mixValue > 1.0f)
            mixValue = 1.0f;
		std::cout << "Mix value: " << mixValue << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        // mix is between 0.0 and 1.0
        mixValue -= 0.01f;
        if (mixValue < 0.0f)
            mixValue = 0.0f;
        std::cout << "Mix value: " << mixValue << std::endl;
    }
    // trying moving camera
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // move camera forward
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.1f));
    }
     if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        // move camera backward
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.1f));
    }
     if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        // move camera left
        view = glm::translate(view, glm::vec3(0.1f, 0.0f, 0.0f));
    }
     if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        // move camera right
        view = glm::translate(view, glm::vec3(-0.1f, 0.0f, 0.0f));
    }
}

int main()
{
 //   glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans = glm::mat4(1.0f);
 //   trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
 //   trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	//vec = trans * vec;
	//std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;




    // GLFW init
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
        glfwCreateWindow(800, 600, "Balls", NULL, NULL);

    glfwMakeContextCurrent(window);

    // GLAD
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Shader
    Shader shader(
        "../../../shaders/rainbow.vert",
        "../../../shaders/rainbow.frag"
    );

    // colors
    //float vertices[] = {
    //    // positions        // colors
    //     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    //    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    //     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    //};
    // for textures
    //float vertices[] = {
    //    // positions // colors // texture coords
    //    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
    //    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    //    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left

    //};

    float vertices[] = {
            // positions              // colors              // texture coords

            // back face
            -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,     0.0f, 1.0f, 0.0f,     1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 0.0f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,     0.0f, 0.0f,

            // front face
            -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 0.0f,     1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 0.0f,     0.0f, 0.0f,

            // left face
            -0.5f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 0.0f,     1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 0.0f,     0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,     1.0f, 0.0f,

            // right face
             0.5f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 0.0f,     1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 0.0f,     0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,     1.0f, 0.0f,

             // bottom face
             -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f,
              0.5f, -0.5f, -0.5f,     0.0f, 1.0f, 0.0f,     1.0f, 1.0f,
              0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
              0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
             -0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 0.0f,     0.0f, 0.0f,
             -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f,

             // top face
             -0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f,
              0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 0.0f,     1.0f, 1.0f,
              0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
              0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
             -0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f,     0.0f, 0.0f,
             -0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f
         };

    // cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };


    // texture

    unsigned int texture1, texture2;

    // texture1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data =
        stbi_load(
            "../../../assets/brick.jpg",
            &width,
            &height,
            &nrChannels,
            0
        );

    if (data)
    {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            width,
            height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data
        );

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << stbi_failure_reason() << std::endl;
    }

    stbi_image_free(data);


    // texture2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data2 =
        stbi_load(
            "../../../assets/awesomeface.png",
            &width,
            &height,
            &nrChannels,
            0
        );

    if (data2)
    {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data2
        );

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << stbi_failure_reason() << std::endl;
    }

    stbi_image_free(data2);

    unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
    };

    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    // Element/index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW
    );

    // position attribute
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(1);
    // texture 
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(6 * sizeof(float))
    );
    glEnableVertexAttribArray(2);


    shader.use();
    shader.setInt("texture2", 1);



    // going 3d
    glm::mat4 model = glm::mat4(1.0f);
    /*model = glm::rotate(model, glm::radians(-55.0f),
        glm::vec3(1.0f, 0.0f, 0.0f));*/

    // rotation
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
        glm::vec3(0.5f, 1.0f, 0.0f));

    // view space
    // glm::mat4 view = glm::mat4(1.0f);
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // projection
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 100.0f);


    unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // z depth
    glEnable(GL_DEPTH_TEST);
    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // shader.use();
        
        // makes it move left to right and right to left and left to right and right to left and left to right and right to left and left to right and right to left
        //float timeValue = glfwGetTime();

        //shader.setFloat(
        //    "xOffset",
        //    sin(timeValue) * 0.5f
        //);

        shader.use();


        shader.setFloat("mixValue", mixValue);
		shader.setMat4("view", view);

        // trying transforms

        /*glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(),glm::vec3(0.0f, 0.0f, 1.0f));

        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO);
        


        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = (float)glfwGetTime() * (20.0f + i * 5.0f);
            model = glm::rotate(model, glm::radians(angle),
                glm::vec3(1.0f, 0.3f, 0.5f));

            shader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);

        }
       

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);

    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
}