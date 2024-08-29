#include "Core/Window.hpp"

#include <stdexcept>

#include "GLFW/glfw3.h"

namespace Saturn {
    Window* Window::s_Window = nullptr;

    Window::Window(const WindowProperties& props) :
        m_UserPointer(new WindowUserPointer { props })
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        auto* window = glfwCreateWindow(props.Width, props.Height, props.WindowName.c_str(), nullptr, nullptr);
        m_NativeWindow = window;
        if (!window)
            throw std::runtime_error("Failed to create GLFW window");

        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, m_UserPointer);
        glfwSwapInterval(props.VSync ? 1 : 0);
    }

    Window::~Window() {
        glfwDestroyWindow(m_NativeWindow);
        glfwTerminate();
    }

    void Window::Run() {
        while (!glfwWindowShouldClose(m_NativeWindow)) {
            glfwPollEvents();
            // Render here...
            glfwSwapBuffers(m_NativeWindow);
        }
    }

    WindowUserPointer* Window::GetUserPointer() const {
        return static_cast<WindowUserPointer*>(glfwGetWindowUserPointer(m_NativeWindow));
    }

    void Window::SetUserPointer(WindowUserPointer* pointer) {
        m_UserPointer = pointer;
        glfwSetWindowUserPointer(m_NativeWindow, pointer);
    }

    Window* Window::CreateWindow(const WindowProperties& props) {
        if (s_Window)
            return s_Window;

        if (!glfwInit())
            return nullptr;

        return new Window(props);
    }
}
