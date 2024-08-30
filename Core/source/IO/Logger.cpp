#include "IO/Logger.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Saturn {
    Logger::Logger(const LoggerProperties& props) {
        spdlog::set_pattern(props.Pattern);
        m_Logger = spdlog::stdout_color_mt(props.Name);
        m_Logger->set_level(spdlog::level::trace);
    }

    Logger::~Logger() = default;
    Logger* Logger::Create(const LoggerProperties& props) {
        return new Logger(props);
    }
}
