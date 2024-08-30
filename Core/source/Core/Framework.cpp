#include "Core/Framework.hpp"

#include "Core/Window.hpp"
#include "GLFW/glfw3.h"

namespace Saturn {
    std::atomic<bool> Framework::s_Initialized = false;
    Window* Framework::s_Window = nullptr;
    Logger* Framework::s_Logger = nullptr;
    Renderer* Framework::s_Renderer = nullptr;
    LayerStack* Framework::s_LayerStack = nullptr;

    bool Framework::Initialize(const LoggerProperties& loggerProps, const WindowProperties& windowProps) {
        if (s_Initialized)
            return false;
        s_Initialized = true;
        s_Logger = Logger::Create(loggerProps);
        s_Window = Window::Create(*s_Logger, windowProps);
        s_Renderer = Renderer::Create(*s_Logger, *s_Window);
        s_LayerStack = LayerStack::Create(*s_Logger, *s_Renderer);
        return true;
    }

    bool Framework::Shutdown() {
        if (!s_Initialized)
            return false;
        delete s_LayerStack;
        delete s_Renderer;
        delete s_Window;
        delete s_Logger;
        s_Initialized = false;
        return true;
    }
}
