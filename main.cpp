
#include "glad/glad.h"
#include "Shader.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

float trans[] = {0.f, 0.f, 0.f};

//SCREEN RESIZING
void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}
//Moving Function
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        trans[0] -= 0.0001f;
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        trans[0] += 0.0001f;
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        trans[1] -= 0.0001f;
    }
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        trans[1] += 0.0001f;
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // CREATE WINDOW
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab1", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //SHADER INITIALIZATION
    std::unique_ptr<Shader> shaderProgram = std::make_unique<Shader>(R"(..\shaders\shader.vs)", R"(..\shaders\shader.fs)");

    float vertices[] = {
            0.175f, 0.45f, 0.0f,
            -0.025f, 0.45f, 0.0f,
            0.075f, 0.35f, 0.0f,
            -0.125f, 0.35f, 0.0f,

            -0.275f, 0.35f, 0.0f,
            -0.275f, 0.2f, 0.0f,
            -0.125f, 0.2f, 0.0f,

            -0.125f, -0.1f, 0.0f,
            0.175f, -0.1f, 0.0f,

            0.175f, -0.4f, 0.0f,

            0.025f, -0.25f, 0.0f,
            -0.125f, -0.4f, 0.0f,

            -0.125f, -0.25f, 0.0f,

            -0.125f, 0.0f, 0.0f,
            -0.225f, -0.1f, 0.0f,
            -0.125f, -0.2f, 0.0f,
    };
    unsigned int indices[] = {
            0, 1, 2,
            1, 2, 3,
            3, 4, 6,
            4, 5, 6,
            6, 7, 8,
            7, 8, 9,
            9, 10, 11,
            10, 11, 12,
            13, 14, 15
    };
    unsigned int indices2[] = {
            0, 1,
            2, 3,
            3, 1,
            0, 2,
            4, 3,
            3, 6,
            6, 5,
            4, 5,
            6, 7,
            7, 8,
            8, 6,
            13, 14,
            14, 15,
            13, 15,
            8, 9,
            7, 9,
            10, 11,
            11, 12,
            12, 10,
            11, 9
    };

    unsigned int VBO, VAO[2], EBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(2, EBO);
    //TRIANGLES
    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //LINES
    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.9f, 0.8f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //TRANSLATE
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(trans[0], trans[1], 0.f));

        glUseProgram(shaderProgram->program);

        unsigned  int transformLoc = glGetUniformLocation(shaderProgram->program, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        //TRIANGLES
        glBindVertexArray(VAO[0]);

        int vertexColorLocation = glGetUniformLocation(shaderProgram->program, "outColor");
        glUniform4f(vertexColorLocation, 0.2f, 0.6f, 1.f, 1.f);

        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, nullptr);
        //LINES
        glBindVertexArray(VAO[1]);
        glUniform4f(vertexColorLocation, 0.f, 0.f, 0.f, 1.f);
        glDrawElements(GL_LINES, sizeof(indices2)/sizeof(int), GL_UNSIGNED_INT, nullptr);

        glUseProgram(shaderProgram->program);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(2, EBO);


    glfwTerminate();
    return 0;
}
