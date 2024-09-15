#include "pch.hpp"
#include "Core/Exception/Exception.hpp"

namespace Saturn {
    Exception::Exception(const std::string& message):
        mMessage(message) {
    }

    Exception::~Exception() noexcept = default;
    const char* Exception::what() const noexcept {
        return mMessage.c_str();
    }
}
