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
constexpr int mWidth = 1280;
constexpr int mHeight = 720;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    fprintf(stderr, "Viewport changed (%d, %d)\n", width, height);
    glViewport(0, 0, mWidth, mHeight);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

#endif //~ Glitter Header
