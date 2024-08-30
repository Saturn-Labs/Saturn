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

    Window& Application::AddWindow(const WindowProperties &props) {
        const Shared<Window> window = Window::Create(*this, props);
        m_Windows.push_back(window);
        return *window;
    }

    Logger& Application::GetLogger() const {
        return *m_Logger;
    }

    Vector<Shared<Window>>& Application::GetWindows() {
        return m_Windows;
    }

    const Vector<Shared<Window>>& Application::GetWindows() const {
        return m_Windows;
    }

    Window* Application::GetCurrentWindow() const {
        return m_CurrentContextWindow;
    }

    Window *Application::SetCurrentWindow(Window *window) {
        Window* oldContextWindow = m_CurrentContextWindow;
        if (!window) {
            m_CurrentContextWindow = nullptr;
            GLFWManager::MakeContextCurrent(nullptr);
            return oldContextWindow;
        }
        m_CurrentContextWindow = window;
        GLFWManager::MakeContextCurrent(window->GetNativeWindow());
        return oldContextWindow;
    }

    void Application::RunApplication() {
        while (!m_Windows.empty()) {
            const Timestep timestep = GLFWManager::Update();
            for (auto it = m_Windows.begin(); it != m_Windows.end();) {
                const auto& window = *it;
                if (window->ShouldClose()) {
                    if (window.get() == GetCurrentWindow())
                        SetCurrentWindow(nullptr);
                    it = m_Windows.erase(it);
                    continue;
                }
                window->Update(timestep);
                ++it;
            }

            GLFWManager::PollEvents();
        }
    }
}
