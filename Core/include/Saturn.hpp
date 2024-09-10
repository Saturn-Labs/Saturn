#pragma once

namespace Saturn {
    class Application;
    class Framework {
    public:
        static Application* sCurrentApplication;
        static Application* GetCurrentApplication();
    };
}