#include "Core/Application.hpp"
#include "Saturn.hpp"
#include "GLFW/glfw3.h"

namespace Saturn {
    Application::Application(const ApplicationProperties& props) :
        mLogger(props.LoggerName),
        mContentManager(props.ContentPath) {
        if (Framework::GetCurrentApplication())
            throw std::exception("Illegal instantiation: Cannot create multiple Application instances!");

        if (!glfwInit()) {
            throw std::exception("Failed to initialize GLFW!");
        }
    }

    Application::~Application() {
        glfwTerminate();
    }

    void Application::Run() {

    }

    Logger& Application::GetLogger() {
        return mLogger;
    }

    ContentManager& Application::GetContentManager() {
        return mContentManager;
    }
}
