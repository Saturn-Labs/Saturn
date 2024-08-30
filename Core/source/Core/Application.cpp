#include "Core/Application.hpp"

#include "Core/GLFWManager.hpp"
#include "Core/Window.hpp"
#include "IO/Logger.hpp"

namespace Saturn {
    Application::Application() {
        m_Logger = Shared<Logger>(Logger::Create());
        GLFWManager::Initialize();
    }

    Application::~Application() {
        GLFWManager::Terminate();
    }

    void Application::AddWindow(const WindowProperties &props) {
        m_Windows.push_back(Window::Create(*this, props));
    }

    Logger& Application::GetLogger() const {
        return *m_Logger;
    }

    Vector<Shared<Window>> & Application::GetWindows() {
        return m_Windows;
    }

    const Vector<Shared<Window>> & Application::GetWindows() const {
        return m_Windows;
    }

    void Application::RunApplication() {
        while (!m_Windows.empty()) {
            for (auto it = m_Windows.begin(); it != m_Windows.end();) {
                const auto& window = *it;
                if (window->ShouldClose()) {
                    it = m_Windows.erase(it);
                    continue;
                }
                window->Update();
                ++it;
            }

            GLFWManager::PollEvents();
        }
    }
}
