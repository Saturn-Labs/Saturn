#pragma once
#include "Common/Types.hpp"
#include <glad/gl.h>
#include "GLFW/glfw3.h"

namespace Saturn {
    class Window;
    struct WindowProperties {
        String Title = "Default Window";
        UInt32 Width = 640;
        UInt32 Height = 480;
        Window* Share = nullptr;
    };

    class Window {
        GLFWwindow* mNativeHandle = nullptr;
        WindowProperties mProperties;
    public:
        Window() = delete;
        explicit Window(const WindowProperties& props);
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&& other) noexcept;
        Window& operator=(Window&& other) noexcept;
        ~Window();

        GLFWwindow* GetNativeHandle() const;
        void MakeContextCurrent();
        bool IsContextCurrent() const;
        bool IsValid() const;

        static GLFWwindow* GetCurrentContext();
        static void ResetCurrentContext();
    };
}
