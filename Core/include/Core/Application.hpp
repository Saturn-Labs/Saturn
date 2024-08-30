#pragma once
#include "Common/Types.hpp"

namespace Saturn {
    struct WindowProperties;
}

namespace Saturn {
    class Logger;
    class Window;

    class Application {
        Shared<Logger> m_Logger;
        Vector<Shared<Window>> m_Windows;

    public:
        Application();
        virtual ~Application();
        void AddWindow(const WindowProperties& props);
        Logger& GetLogger() const;
        Vector<Shared<Window>>& GetWindows();
        const Vector<Shared<Window>>& GetWindows() const;
        void RunApplication();
    };
}
