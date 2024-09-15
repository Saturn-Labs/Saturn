#include "pch.hpp"
#include "Core/Logger.hpp"

namespace Saturn {
    std::shared_ptr<spdlog::logger> Logger::sNativeLogger = nullptr;
    bool Logger::sInitialized = false;

    void Logger::Initialize(const std::string& name) {
        if (sInitialized)
            return;
        sInitialized = true;
        if (sNativeLogger)
            spdlog::drop(sNativeLogger->name());
        sNativeLogger = spdlog::stdout_color_mt(name);
        sNativeLogger->set_level(spdlog::level::trace);
        sNativeLogger->set_pattern("%^[%T] %n: %v%$");
    }

    void Logger::Shutdown() {
        if (!sInitialized)
            return;
        sInitialized = false;
        spdlog::drop(sNativeLogger->name());
        sNativeLogger.reset();
    }
}
