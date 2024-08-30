#pragma once
#include "Application.hpp"

namespace Saturn {
    extern Application* CreateApplication();
}

inline int main() {
    try {
        auto* app = Saturn::CreateApplication();
        app->RunApplication();
    }
    catch (const std::exception& e) {
        std::cerr << fmt::format("SaturnFramework threw an exception: {}", e.what()) << std::endl;
        return 1;
    }
    return 0;
}