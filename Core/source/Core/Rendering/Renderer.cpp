#include "Core/Rendering/Renderer.hpp"

namespace Saturn {
    void Renderer::Initialize() {
        if (!glfwInit())
            throw std::exception("Failed to initialize GLFW!");
    }

    void Renderer::Shutdown() {
        glfwTerminate();
    }

    void Renderer::BeginUpdate() {
        if (!glfwGetCurrentContext())
            throw std::exception("Can't begin update without a bound context!");
    }

    void Renderer::EndUpdate() {
        if (!glfwGetCurrentContext())
            throw std::exception("Can't end update without a bound context!");
    }
}