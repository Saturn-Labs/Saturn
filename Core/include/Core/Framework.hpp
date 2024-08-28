#pragma once
#include "Types.hpp"

namespace Saturn {
    class Framework {
    public:
        Framework() = default;
        Framework(const Framework&) = delete;
        Framework& operator=(const Framework&) = delete;
        Framework(Framework&&) = delete;
        Framework& operator=(Framework&&) = delete;
        static Unique<Framework> CreateInstance();
    };
}
