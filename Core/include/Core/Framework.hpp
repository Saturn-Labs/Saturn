#pragma once
#include "Window.hpp"
#include "Common/Types.hpp"

namespace Saturn {
    class Framework {
    private:
        static bool s_Initialized;
        static Window* s_Window;

    public:
        Framework() = delete;
        Framework(const Framework&) = delete;
        Framework(Framework&&) = delete;
        Framework& operator=(const Framework&) = delete;
        Framework& operator=(Framework&&) = delete;

        static bool Initialize(const WindowProperties& props = {});
        static bool Shutdown();
        static bool IsInitialized() {
            return s_Initialized;
        }

        static Window& GetWindow() {
            return *s_Window;
        }
    };
}
