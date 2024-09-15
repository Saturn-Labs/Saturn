#pragma once
#include "Common/Types.hpp"

namespace Saturn {
    class Logger {
        static bool sInitialized;
        static std::shared_ptr<spdlog::logger> sNativeLogger;
    public:
        static void Initialize(const std::string& name);
        static void Shutdown();

        template<typename... Args>
        static void Debug(const spdlog::format_string_t<Args...>& format, Args&&... args) {
            #ifdef _DEBUG
            sNativeLogger->trace(format, std::forward<Args>(args)...);
            #endif
        }

        template<typename... Args>
        static void Trace(const spdlog::format_string_t<Args...>& format, Args&&... args) {
            sNativeLogger->trace(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Info(const spdlog::format_string_t<Args...>& format, Args&&... args) {
            sNativeLogger->info(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Warn(const spdlog::format_string_t<Args...>& format, Args&&... args) {
            sNativeLogger->warn(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Error(const spdlog::format_string_t<Args...>& format, Args&&... args) {
            sNativeLogger->error(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Critical(const spdlog::format_string_t<Args...>& format, Args&&... args) {
            sNativeLogger->critical(format, std::forward<Args>(args)...);
        }
    };
}
