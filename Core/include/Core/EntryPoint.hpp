#pragma once
#include "Application.hpp"

namespace Saturn {
    extern Application* CreateApplication();
}

int main() {
    auto* app = Saturn::CreateApplication();
    app->RunApplication();
    return 0;
}