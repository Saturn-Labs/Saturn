#pragma once
#include <exception>
#include <string>

namespace Saturn {
    class Exception final : public std::exception {
        std::string mMessage;
    public:
        explicit Exception(const std::string& message);
        ~Exception() noexcept override;
        const char* what() const noexcept override;
    };
}
