#include "Core/Framework.hpp"

#include "Core/Window.hpp"
#include "GLFW/glfw3.h"

namespace Saturn {
    bool Framework::s_Initialized = false;
    Window* Framework::s_Window = nullptr;

    bool Framework::Initialize(const WindowProperties& props) {
        if (s_Initialized)
            return false;
        s_Initialized = true;
        s_Window = Window::Create(props);
        return true;
    }

    bool Framework::Shutdown() {
        if (!s_Initialized)
            return false;
        delete s_Window;
        s_Initialized = false;
        return true;
    }
}
