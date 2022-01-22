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

// Define Some Constants
constexpr int mWidth = 1200;
constexpr int mHeight = 900;

inline void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    fprintf(stderr, "Viewport changed (%d, %d)\n", width, height);
    glViewport(0, 0, mWidth, mHeight);
}

inline void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

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
        snprintf(title, 255, "%s %s - [FPS: %d]", "OpenGL", "4.0", nbFrames);
        glfwSetWindowTitle(win, title);

        nbFrames = 0;
        lastTime += 1.0;
    }
}

#endif //~ Glitter Header
