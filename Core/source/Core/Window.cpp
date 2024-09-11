#include "Core/Window.hpp"
#include <spdlog/fmt/bundled/format.h>
#include "Saturn.hpp"
#include "Common/Types.hpp"
#include "Core/Application.hpp"

namespace Saturn {
    Window::Window(const WindowProperties& props) :
        mProperties(props) {
        const Logger& logger = Framework::GetCurrentApplication()->GetLogger();
        logger.Trace("Creating window '{}' with size of {}x{}...", props.Title, props.Width, props.Height);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        mNativeHandle = glfwCreateWindow(
            props.Width,
            props.Height,
            props.Title.c_str(),
            nullptr,
            props.Share ? props.Share->GetNativeHandle() : nullptr);

        if (!mNativeHandle) {
            throw Exception(fmt::format("Could not create '{}' window!", props.Title).c_str());
        }

        auto* currentCtx = GetCurrentContext();
        glfwMakeContextCurrent(mNativeHandle);
        const Int32 version = gladLoadGL(glfwGetProcAddress);
        if (version == 0) {
            logger.Error("Failed to initialize OpenGL context for window '{}'!", props.Title);
            return;
        }
        logger.Info("Initialized OpenGL {} for window '{}'!", reinterpret_cast<CString>(glGetString(GL_VERSION)), props.Title);
        glfwMakeContextCurrent(currentCtx);
    }

    Window::Window(Window&& other) noexcept :
        mNativeHandle(std::exchange(other.mNativeHandle, nullptr)),
        mProperties(std::move(other.mProperties)) {
    }

    Window& Window::operator=(Window&& other) noexcept {
        if (this != &other) {
            mNativeHandle = std::exchange(other.mNativeHandle, nullptr);
            mProperties = std::move(other.mProperties);
        }
        return *this;
    }

    Window::~Window() {
        if (!IsValid())
            return;
        glfwDestroyWindow(mNativeHandle);
    }

    GLFWwindow* Window::GetNativeHandle() const {
        return mNativeHandle;
    }

    void Window::MakeContextCurrent() {
        glfwMakeContextCurrent(GetNativeHandle());
    }

    bool Window::IsContextCurrent() const {
        return GetNativeHandle() == GetCurrentContext();
    }

    bool Window::IsValid() const {
        return mNativeHandle != nullptr;
    }

    GLFWwindow* Window::GetCurrentContext() {
        return glfwGetCurrentContext();
    }

    void Window::ResetCurrentContext() {
        glfwMakeContextCurrent(nullptr);
    }
}
