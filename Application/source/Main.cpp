#include <iostream>

#include "Core/Application.hpp"
#include "Core/Timestep.hpp"
#include "Core/Window.hpp"
#include "glm/glm.hpp"
#include "IO/File.hpp"
#include "IO/Logger.hpp"
#include "Core/EntryPoint.hpp"
using namespace Saturn;

namespace Saturn {
    Application* CreateApplication() {
        auto* app = new Application();
        app->AddWindow({});
        return app;
    }
}
