#include "Core/Window.hpp"

#include <stdexcept>

#include "Core/Application.hpp"
#include "Core/Timestep.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "IO/Logger.hpp"

namespace Saturn {
    Window::Window(Application& application, const WindowProperties& props) :
        m_Application(application),
        m_UserPointer(new WindowUserPointer { props })
    {
        auto* window = glfwCreateWindow(props.Width, props.Height, props.WindowName.c_str(), nullptr, nullptr);
        m_NativeWindow = window;
        if (!window)
            throw std::runtime_error("Failed to create GLFW window");

        application.GetLogger().Trace("Created GLFW window: {}", props.WindowName);

        glfwSetWindowUserPointer(m_NativeWindow, m_UserPointer);
        glfwMakeContextCurrent(m_NativeWindow);
        glfwSwapInterval(m_UserPointer->Properties.VSync ? 1 : 0);
        glfwMakeContextCurrent(nullptr);
    }

    Window::~Window() {
        glfwDestroyWindow(m_NativeWindow);
        delete m_UserPointer;
    }

    void Window::Update() {
        // Render
        glfwSwapBuffers(m_NativeWindow);
    }

    WindowUserPointer* Window::GetUserPointer() const {
        return static_cast<WindowUserPointer*>(glfwGetWindowUserPointer(m_NativeWindow));
    }

    void Window::SetUserPointer(WindowUserPointer* pointer) {
        m_UserPointer = pointer;
        glfwSetWindowUserPointer(m_NativeWindow, pointer);
    }

    Application& Window::GetApplication() const  {
        return m_Application;
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_NativeWindow);
    }

    Shared<Window> Window::Create(Application &application, const WindowProperties &props) {
        auto window = Shared<Window>(new Window(application, props));
        return window;
    }
}
