#include "Core/GLFWManager.hpp"

#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Saturn {
    void GLFWManager::Initialize() {
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void GLFWManager::Terminate() {
        glfwTerminate();
    }

    void GLFWManager::PollEvents() {
        glfwPollEvents();
    }
}
