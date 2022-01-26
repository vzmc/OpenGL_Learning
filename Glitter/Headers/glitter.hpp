// Preprocessor Directives
#ifndef GLITTER
#define GLITTER
#pragma once

// System Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <btBulletDynamicsCommon.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
//     #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "GLFW/glfw3.h"

#include <iostream>

// Define Some Constants
constexpr int SCR_WIDTH = 1200;
constexpr int SCR_HEIGHT = 900;

inline void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    fprintf(stderr, "Viewport changed (%d, %d)\n", width, height);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

inline void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

double deltaTime = 0.0;
double lastFrame = 0.0;

int    FPS = 0;
int    nbFrames = 0;
double lastTime = 0.0;
inline void set_window_fps(GLFWwindow* win) {
    // Measure speed
    const double currentTime = glfwGetTime();
    nbFrames++;

    if (currentTime - lastTime >= 1.0) {
        // If last cout was more than 1 sec ago
        char title[256];
        title[255] = '\0';
        FPS = nbFrames;
        snprintf(title, 255, "%s %s - [FPS: %d]", "OpenGL", "4.0", FPS);
        glfwSetWindowTitle(win, title);

        nbFrames = 0;
        lastTime += 1.0;
    }
}

// 读取纹理
inline GLuint load_image(const char* fileName, GLint channelMode) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    GLint width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    const auto data = stbi_load(fileName, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, channelMode, width, height, 0, channelMode, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    return texture;
}

#endif //~ Glitter Header
