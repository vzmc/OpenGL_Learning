#pragma once

// System Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Headers
#include <string>

// Define Namespace
namespace Mirage {
class Shader {
public:
    // Implement Custom Constructor and Destructor
    Shader() {
        mProgram = glCreateProgram();
    }

    ~Shader() {
        glDeleteProgram(mProgram);
    }

    // Public Member Functions
    Shader& activate();
    Shader& attach(const std::string& filename);
    GLuint  create(const std::string& filename);

    GLuint get() {
        return mProgram;
    }

    Shader& link();

    // Wrap Calls to glUniform
    void bind(unsigned int location, int value);
    void bind(unsigned int location, float value);
    void bind(unsigned int location, const glm::mat4& matrix);

    template <typename T>
    Shader& bind(const std::string& name, T&& value) {
        int location = glGetUniformLocation(mProgram, name.c_str());
        if (location == -1) {
            fprintf(stderr, "Missing Uniform: %s\n", name.c_str());
        } else {
            bind(location, std::forward<T>(value));
        }
        return *this;
    }

private:
    // Disable Copying and Assignment
    Shader(const Shader&)            = delete;
    Shader& operator=(const Shader&) = delete;

    // Private Member Variables
    GLuint mProgram;
    GLint  mStatus;
    GLint  mLength;
};
};
