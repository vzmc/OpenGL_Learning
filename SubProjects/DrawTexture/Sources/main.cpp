// Local Headers
#include "header.hpp"

// GlitterLib Header
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

#include <shader.hpp>

constexpr double PI = 3.1415926535897932384626433832795;

int main(int argc, char* argv[]) {
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    const auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    // 定义三角形的顶点和相位差
    float vertices[] = {
        // 位置              // 相位差
         0.5f, -0.5f, 0.0f,  0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  1.0f,   // 左下
         0.0f,  0.5f, 0.0f,  2.0f    // 顶部
    };

    // 创建VAO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    // 绑定VAO
    glBindVertexArray(VAO);

    // 创建VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    // 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 设置顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);
    // 设置相位差属性
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // 创建一个shader
    Mirage::Shader shader;
    shader.attach("transColorful.vert")
          .attach("transColorful.frag");
    shader.link();

    // 设置为线框模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 设置为填充模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // 激活shader
    shader.activate();
    int piLocation = glGetUniformLocation(shader.get(), "PI");
    int phaseLocation = glGetUniformLocation(shader.get(), "phase");
    glUniform1f(piLocation, PI);
    glUniform1f(phaseLocation, PI * 2.0 / 3.0);

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        process_input(mWindow);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 激活shader
        shader.activate();
        float time = glfwGetTime();
        int timeLocation = glGetUniformLocation(shader.get(), "time");
        glUniform1f(timeLocation, time);

        glBindVertexArray(VAO);
        // 绘制索引图形
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
