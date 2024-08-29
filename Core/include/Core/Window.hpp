﻿#pragma once
#include "Common/Types.hpp"

class GLFWwindow;
namespace Saturn {
    struct WindowProperties {
        String WindowName = "Default Window";
        int Width = 640;
        int Height = 480;
        bool VSync = true;
    };

    struct WindowUserPointer {
        WindowProperties Properties;
    };

    class Window {
    private:
        WindowUserPointer* m_UserPointer;
        GLFWwindow* m_NativeWindow;
        double m_LastFrameTime;

    private:
        explicit Window(const WindowProperties& props);

    public:
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;
        ~Window();

    public:
        void Run();
        WindowUserPointer* GetUserPointer() const;
        void SetUserPointer(WindowUserPointer* pointer);

    public:
        static Window* Create(const WindowProperties& props = WindowProperties());
        static Window* GetInstance();
    };
}
