#pragma once
#include "Logger.hpp"
#include "Common/Types.hpp"
#include "Content/ContentManager.hpp"

namespace Saturn {
    class Window;
    struct ApplicationProperties {
        String LoggerName = "Application";
        String ContentPath = "assets/";
    };

    class Application {
    protected:
        Logger mLogger;
        ContentManager mContentManager;
    public:
        explicit Application(const ApplicationProperties& props = {});
        virtual ~Application();
        virtual void Run();

        Logger& GetLogger();
        ContentManager& GetContentManager();
    };
}
