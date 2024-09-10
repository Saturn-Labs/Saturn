#pragma once
#include "Application.hpp"
#include "Common/Types.hpp"
#include "Logger.hpp"
#include "Saturn.hpp"

namespace Saturn {
    extern Application* CreateApplication();
}

inline int main() {
    try {
        Saturn::Framework::sCurrentApplication = Saturn::CreateApplication();
    }
    catch (const std::exception& e) {
        std::cout << fmt::format("Application creation exception: {}", e.what()) << std::endl;
    }

    try {
        Saturn::Framework::sCurrentApplication->Run();
    }
    catch (const std::exception& e) {
        Saturn::Framework::sCurrentApplication->GetLogger().Info("Application running exception: {}", e.what());
    }
    delete Saturn::Framework::sCurrentApplication;
    return 0;
}