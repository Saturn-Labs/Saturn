#include <glad/gl.h>
#include <stdexcept>
#include "Core/Window.hpp"
#include "Core/Application.hpp"
#include "Core/Timestep.hpp"
#include "IO/Logger.hpp"

namespace Saturn {
    Window::Window(Application& application, const WindowProperties& props) :
        m_Application(application),
        m_UserPointer(nullptr),
        m_LayerStack(LayerStack(*this))
    {
        GLFWManager::SetWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        GLFWManager::SetWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        GLFWManager::SetWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        auto* window = GLFWManager::CreateNewWindow(props.Width, props.Height, props.WindowName.c_str(), nullptr, nullptr);
        m_NativeWindow = window;
        if (!window)
            throw std::runtime_error("Failed to create GLFW window");

        application.GetLogger().Trace("Created GLFW window: {}", props.WindowName);
        SetUserPointer(new WindowUserPointer { props });

        Window* oldContextWindow = application.SetCurrentWindow(this);
        GLFWManager::SetSwapInterval(m_UserPointer->Properties.VSync ? 1 : 0);
        int version;
        if ((version = gladLoadGL(glfwGetProcAddress)) == 0)
            throw std::exception("Failed to load OpenGL for Window.");
        application.GetLogger().Trace("Loaded OpenGL {}.{} for '{}'", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version), props.WindowName);
        application.SetCurrentWindow(oldContextWindow);
    }

    Window::~Window() {
        GLFWManager::DestroyWindow(m_NativeWindow);
        m_Application.GetLogger().Trace("Destroyed window '{}'", m_UserPointer->Properties.WindowName);
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
