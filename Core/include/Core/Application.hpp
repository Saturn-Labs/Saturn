#pragma once
#include "Common/Types.hpp"

namespace Saturn {
    struct Timestep;
    struct WindowProperties;
}

namespace Saturn {
    class Logger;
    class Window;

    class Application {
    protected:
        Shared<Logger> m_Logger;
        Vector<Shared<Window>> m_Windows;
        Window* m_CurrentContextWindow = nullptr;

    public:
        Application();
        virtual ~Application();
        Window& AddWindow(const WindowProperties& props);
        Logger& GetLogger() const;
        Vector<Shared<Window>>& GetWindows();
        const Vector<Shared<Window>>& GetWindows() const;
        Window* GetCurrentWindow() const;

        Window *SetCurrentWindow(Window *window);
        void RunApplication();

        virtual void Start() = 0;
        virtual void Update(Timestep deltaTime) = 0;
    };
}
