#include <iostream>

#include "Application/MyApplication.hpp"
#include "Core/Application.hpp"
#include "Core/Timestep.hpp"
#include "Core/Window.hpp"
#include "glm/glm.hpp"
#include "IO/File.hpp"
#include "IO/Logger.hpp"
#include "Core/EntryPoint.hpp"

Saturn::Application* Saturn::CreateApplication() {
    auto* app = new MyApplication();
    return app;
}