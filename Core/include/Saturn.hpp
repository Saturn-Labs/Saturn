#pragma once

#if !defined(LOGGER_NAME)
#define LOGGER_NAME "Application"
#endif

namespace Saturn {
    class ResourceManager;
    class Application;
    extern Application* CreateApplication();
    class Framework {
    public:
        static Application* sApplication;
        static ResourceManager* sResourceManager;
        static bool sInitialized;

        static void Initialize();
        static void Shutdown();

        static Application* GetApplication();
        static ResourceManager* GetResourceManager();
    };
}
