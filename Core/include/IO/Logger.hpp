#pragma once
#include <spdlog/spdlog.h>
#include "Common/Types.hpp"

namespace Saturn {
    struct LoggerProperties {
        String Name = "Saturn Framework";
        String Pattern = "%^[%T] %n: %v%$";
    };

    class Logger {
    private:
        Shared<spdlog::logger> m_Logger;
        explicit Logger(const LoggerProperties& props);

    public:
        Logger() = delete;
        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;
        ~Logger();

        static Logger* Create(const LoggerProperties& props = {});

        template<typename... Args>
        void Trace(spdlog::format_string_t<Args...> format, Args&&... args) {
            m_Logger->trace(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Info(spdlog::format_string_t<Args...> format, Args&&... args) {
            m_Logger->info(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Warn(spdlog::format_string_t<Args...> format, Args&&... args) {
            m_Logger->warn(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Error(spdlog::format_string_t<Args...> format, Args&&... args) {
            m_Logger->error(format, std::forward<Args>(args)...);
        }
    };
}
