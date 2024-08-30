#pragma once
#include <glm/vec4.hpp>

namespace Saturn {
    struct Timestep;
}

namespace Saturn {
    class Window;
    class Logger;

    class Renderer {
    private:
        Renderer(Logger& logger, Window& window);

    public:
        Renderer() = delete;
        Renderer(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(Renderer&&) = delete;
        ~Renderer();

        static Renderer* Create(Logger& logger, Window& window);
        void Clear(const glm::vec4& clearColor = { 0, 0, 0.4, 1 });
        void Render(const Timestep& timestep);
    };
}
