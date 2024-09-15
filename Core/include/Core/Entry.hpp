#pragma once
#include "Application.hpp"
#include "Common/Types.hpp"
#include "Logger.hpp"
#include "Saturn.hpp"

inline int main() {
    try {
        Saturn::Framework::Initialize();
        Saturn::Framework::GetApplication()->Run();
    }
    catch (const std::exception& e) {
        Saturn::Logger::Error("Unhandled exception: {}", e.what());
    }
    return 0;
}