#include <glad/glad.h>
#include <stdexcept>
#include "Core/Window.hpp"
#include "Core/Application.hpp"
#include "Core/Timestep.hpp"
#include "IO/Logger.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Saturn {
    Window::Window(Application& application, const WindowProperties& props) :
        m_Application(application),
        m_UserPointer(nullptr),
        m_LayerStack(LayerStack(*this))
    {
        GLFWManager::SetWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        GLFWManager::SetWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        GLFWManager::SetWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        auto* window = GLFWManager::CreateNewWindow(props.Width, props.Height, props.WindowName.c_str(), nullptr, nullptr);
        m_NativeWindow = window;
        if (!window)
            throw std::runtime_error("Failed to create GLFW window");

        application.GetLogger().Trace("Created GLFW window: {}", props.WindowName);
        SetUserPointer(new WindowUserPointer { props });

        Window* oldContextWindow = application.SetCurrentWindow(this);
        GLFWManager::SetSwapInterval(m_UserPointer->Properties.VSync ? 1 : 0);
        if (int version; (version = gladLoadGL()) == 0)
            throw std::exception("Failed to load OpenGL for Window.");
        application.GetLogger().Trace("Loaded OpenGL {} for '{}'", reinterpret_cast<CString>(glGetString(GL_VERSION)), props.WindowName);
        application.SetCurrentWindow(oldContextWindow);
    }

    Window::~Window() {
        Window* oldContextWindow = GetApplication().SetCurrentWindow(this);

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        GLFWManager::DestroyWindow(m_NativeWindow);
        GetApplication().SetCurrentWindow(oldContextWindow);
        GetApplication().GetLogger().Trace("Destroyed window '{}'", m_UserPointer->Properties.WindowName);
        delete m_UserPointer;
    }

    void Window::Update(Timestep timestep) {
        Application& app = GetApplication();
        Logger& logger = app.GetLogger();
        app.SetCurrentWindow(this);
        m_LayerStack.Update(timestep);
        GLFWManager::SwapBuffers(m_NativeWindow);
    }

    WindowUserPointer* Window::GetUserPointer() const {
        return GLFWManager::GetWindowUserPointer<WindowUserPointer>(m_NativeWindow);
    }

    GLFWwindow* Window::GetNativeWindow() const {
        return m_NativeWindow;
    }

    void Window::SetUserPointer(WindowUserPointer* pointer) {
        m_UserPointer = pointer;
        GLFWManager::SetWindowUserPointer(m_NativeWindow, pointer);
    }

    Application& Window::GetApplication() const  {
        return m_Application;
    }

    const LayerStack& Window::GetLayerStack() const {
        return m_LayerStack;
    }

    LayerStack& Window::GetLayerStack() {
        return m_LayerStack;
    }

    bool Window::ShouldClose() const {
        return GLFWManager::WindowShouldClose(m_NativeWindow);
    }

    Shared<Window> Window::Create(Application &application, const WindowProperties &props) {
        auto window = Shared<Window>(new Window(application, props));
        return window;
    }
}
