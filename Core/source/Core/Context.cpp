#include "pch.hpp"
#include "Core/Context.hpp"
#include "Common/Types.hpp"
#include "Core/Application.hpp"
#include "Core/Logger.hpp"
#include "Core/Resource/ResourceManager.hpp"
#include "Saturn.hpp"

namespace Saturn {
    ContextMap Context::sContexts = {};

    Context::Context(const ContextProperties& properties) :
        mProperties(properties) {
    }

    Context::~Context() {
        glfwDestroyWindow(GetNativeHandle());
    }

    GLFWwindow* Context::GetNativeHandle() const {
        return mNativeHandle;
    }

    bool Context::IsValidContext() const {
        return mNativeHandle != nullptr;
    }

    void Context::SetThisAsCurrentContext() const {
        if (!IsValidContext())
            return;
        SetCurrentContext(*this);
    }

    bool Context::ShouldClose() const {
        if (!IsValidContext())
            return false;
        return glfwWindowShouldClose(mNativeHandle);
    }

    void Context::SwapBuffers() const {
        if (!IsValidContext())
            return;
        glfwSwapBuffers(mNativeHandle);
    }

    void Context::Update(const Timestep& time) {

    }

    ContextProperties& Context::GetProperties() {
        return mProperties;
    }

    const ContextProperties& Context::GetProperties() const {
        return mProperties;
    }

    std::weak_ptr<Context> Context::Create(const ContextProperties& properties) {
        std::shared_ptr<Context> context = std::shared_ptr<Context>(new Context(properties));

#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
        glfwWindowHint(GLFW_VISIBLE, !properties.Windowless);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        context->mNativeHandle = glfwCreateWindow(
            properties.WindowProperties.Width,
            properties.WindowProperties.Height,
            properties.WindowProperties.Title.c_str(),
            nullptr,
            Framework::GetResourceManager() ? Framework::GetResourceManager()->GetContext().GetNativeHandle() : nullptr);
        glfwDefaultWindowHints();

        if (!context->GetNativeHandle()) {
            throw std::exception(fmt::format("Could not create context!").c_str());
        }
        sContexts[context->GetNativeHandle()] = context;

        const auto lastContext = GetCurrentContext();
        context->SetThisAsCurrentContext();
        if (gladLoadGL(glfwGetProcAddress) == 0) {
            throw std::exception("Failed to initialize OpenGL for context!");
        }

        glfwSwapInterval(static_cast<Int32>(properties.WindowProperties.Sync));

#ifdef _DEBUG
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(&Context::OnError, context.get());
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
#endif

        Logger::Info("Initialized OpenGL {} for context!", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glfwMakeContextCurrent(nullptr);
        return context;
    }

    void Context::SetCurrentContext(const Context& context) {
        if (!context.IsValidContext())
            throw std::exception("Cannot set a invalid context as current!");
        glfwMakeContextCurrent(context.GetNativeHandle());
    }

    std::weak_ptr<Context> Context::GetCurrentContext() {
        auto* nativeHandle = glfwGetCurrentContext();
        if (!nativeHandle || !sContexts.contains(nativeHandle))
            return std::weak_ptr<Context>();
        return sContexts[nativeHandle];
    }

    ContextMap& Context::GetContexts() {
        return sContexts;
    }

    void Context::PollEvents() { glfwPollEvents(); }
    void Context::OnError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
        const Context* ctx = static_cast<const Context*>(userParam);
        std::string sourceString;
        std::string typeString;
        switch (source)
        {
            case GL_DEBUG_SOURCE_API:             sourceString = "API"; break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceString = "Window System"; break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceString = "Shader Compiler"; break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceString = "Third Party"; break;
            case GL_DEBUG_SOURCE_APPLICATION:     sourceString = "Application"; break;
            case GL_DEBUG_SOURCE_OTHER:           sourceString = "Other"; break;
        }

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:               typeString = "Error"; break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeString = "Deprecated Behaviour"; break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeString = "Undefined Behaviour"; break;
            case GL_DEBUG_TYPE_PORTABILITY:         typeString = "Portability"; break;
            case GL_DEBUG_TYPE_PERFORMANCE:         typeString = "Performance"; break;
            case GL_DEBUG_TYPE_MARKER:              typeString = "Marker"; break;
            case GL_DEBUG_TYPE_PUSH_GROUP:          typeString = "Push Group"; break;
            case GL_DEBUG_TYPE_POP_GROUP:           typeString = "Pop Group"; break;
            case GL_DEBUG_TYPE_OTHER:               typeString = "Other"; break;
        }

        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            Logger::Error("OpenGL Error from '{}'.. {} - {}: {}", ctx->GetProperties().WindowProperties.Title, sourceString, typeString, message);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            Logger::Warn("OpenGL Warn from '{}'.. {} - {}: {}", ctx->GetProperties().WindowProperties.Title, sourceString, typeString, message);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            Logger::Info("OpenGL Info from '{}'.. {} - {}: {}", ctx->GetProperties().WindowProperties.Title, sourceString, typeString, message);
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            Logger::Trace("OpenGL Trace from '{}'.. {} - {}: {}", ctx->GetProperties().WindowProperties.Title, sourceString, typeString, message);
            break;
        }
    }
} // namespace Saturn
