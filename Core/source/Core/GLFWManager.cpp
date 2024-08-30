#include "Core/GLFWManager.hpp"
#include <stdexcept>

namespace Saturn {
    double GLFWManager::s_LastUpdateTime = 0.0;
    void GLFWManager::Initialize() {
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");
    }

    void GLFWManager::Terminate() {
        glfwTerminate();
    }

    void GLFWManager::PollEvents() {
        glfwPollEvents();
    }

    void GLFWManager::MakeContextCurrent(GLFWwindow *window) {
        glfwMakeContextCurrent(window);
    }

    void GLFWManager::SetSwapInterval(int interval) {
        glfwSwapInterval(interval);
    }

    bool GLFWManager::WindowShouldClose(GLFWwindow *window) {
        return glfwWindowShouldClose(window);
    }

    Timestep GLFWManager::Update() {
        const double currentTime = GetTime();
        const double deltaTime = currentTime - s_LastUpdateTime;
        s_LastUpdateTime = currentTime;
        return { deltaTime };
    }

    double GLFWManager::GetTime() {
        return glfwGetTime();
    }

    void GLFWManager::SwapBuffers(GLFWwindow* window) {
        glfwSwapBuffers(window);
    }

    void GLFWManager::SetWindowHint(int hint, int value) {
        glfwWindowHint(hint, value);
    }

    GLFWwindow* GLFWManager::CreateNewWindow(int width, int height, CString title, GLFWmonitor *monitor, GLFWwindow *share) {
        return glfwCreateWindow(width, height, title, monitor, share);
    }

    void GLFWManager::DestroyWindow(GLFWwindow *window) {
        glfwDestroyWindow(window);
    }
}
