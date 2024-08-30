#include "Core/Rendering/Renderer.hpp"
#include "Core/Framework.hpp"
#include "glad/gl.h"
#include "GLFW/glfw3.h"

namespace Saturn {
    Renderer::Renderer(Logger &logger, Window &window) {
        const int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0)
            throw std::runtime_error("Failed to initialize OpenGL!");

        logger.Info("OpenGL {}.{} loaded succesfully!", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    }

    Renderer::~Renderer() = default;
    Renderer* Renderer::Create(Logger &logger, Window &window) {
        if (Framework::HasRenderer())
            return &Framework::GetRenderer();

        return new Renderer(logger, window);
    }

    void Renderer::Clear(const glm::vec4 &clearColor) {
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::Render(const Timestep &timestep) {

    }
}
