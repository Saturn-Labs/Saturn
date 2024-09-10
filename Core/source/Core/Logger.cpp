#include "Core/Logger.hpp"

namespace Saturn {
    Logger::Logger(const String& name) :
        mNativeLogger(spdlog::stdout_color_mt(name))
    {
        mNativeLogger->set_level(spdlog::level::trace);
        mNativeLogger->set_pattern("%^[%T] %n: %v%$");
    }

    Logger::~Logger() {
        spdlog::drop(mNativeLogger->name());
    }
}
