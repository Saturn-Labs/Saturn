#pragma once
#include "Common/Types.hpp"

namespace Saturn {
    class Framework {
    private:
        static bool s_Initialized;

    public:
        Framework() = delete;
        Framework(const Framework&) = delete;
        Framework& operator=(const Framework&) = delete;
        Framework(Framework&&) = delete;
        Framework& operator=(Framework&&) = delete;

        static void Initialize();
        static void Shutdown();
    };
}
