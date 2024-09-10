#pragma once
#include "Common/Types.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/std.h"

namespace Saturn {
    class Logger final {
        Shared<spdlog::logger> mNativeLogger = nullptr;
    public:
        Logger() = delete;
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = delete;
        explicit Logger(const String& name);
        ~Logger();

        template<typename... Args>
        void Trace(const spdlog::format_string_t<Args...>& format, Args&&... args) const {
            mNativeLogger->trace(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Info(const spdlog::format_string_t<Args...>& format, Args&&... args) const {
            mNativeLogger->info(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Warn(const spdlog::format_string_t<Args...>& format, Args&&... args) const {
            mNativeLogger->warn(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Error(const spdlog::format_string_t<Args...>& format, Args&&... args) const {
            mNativeLogger->error(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Critical(const spdlog::format_string_t<Args...>& format, Args&&... args) const {
            mNativeLogger->critical(format, std::forward<Args>(args)...);
        }
    };
}
