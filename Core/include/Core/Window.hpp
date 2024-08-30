#pragma once
#include <thread>
#include "Common/Types.hpp"

class GLFWwindow;
namespace Saturn {
    class Application;

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
        Application& m_Application;
        WindowUserPointer* m_UserPointer;
        GLFWwindow* m_NativeWindow;
        double m_LastFrameTime = 0;

    public:
        explicit Window(Application& application, const WindowProperties& props);
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;
        ~Window();

        void Update();
        void SetUserPointer(WindowUserPointer* pointer);
        WindowUserPointer* GetUserPointer() const;
        Application& GetApplication() const;
        bool ShouldClose() const;

        static Shared<Window> Create(Application& application, const WindowProperties& props = {});
    };
}
