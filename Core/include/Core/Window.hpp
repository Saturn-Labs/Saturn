#pragma once
#include <thread>
#include "Common/Types.hpp"
#include "LayerSystem/LayerStack.hpp"
#include "Core/GLFWManager.hpp"

namespace Saturn {
    struct Timestep;
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
        LayerStack m_LayerStack;

    public:
        explicit Window(Application& application, const WindowProperties& props);
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;
        ~Window();

        void Update(Timestep timestep);
        void SetUserPointer(WindowUserPointer* pointer);
        WindowUserPointer* GetUserPointer() const;
        GLFWwindow* GetNativeWindow() const;
        Application& GetApplication() const;
        const LayerStack& GetLayerStack() const;
        LayerStack& GetLayerStack();
        bool ShouldClose() const;

        static Shared<Window> Create(Application& application, const WindowProperties& props = {});
    };
}
