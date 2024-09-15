#pragma once
#include "Common/Timestep.hpp"
#include "Common/Types.hpp"

namespace Saturn {
    class Context;
    enum class FrameSync {
        Adaptative = -1,
        None = 0,
        Vertical = 1,
    };

    struct WindowProperties {
        std::string Title = "Default Window";
        int Width = 640;
        int Height = 480;
        FrameSync Sync = FrameSync::Vertical;
    };

    struct ContextProperties {
        bool Windowless = false;
        WindowProperties WindowProperties = {};
    };

    using ContextMap = std::unordered_map<GLFWwindow*, std::shared_ptr<Context>>;
    class Context {
        static ContextMap sContexts;

        GLFWwindow* mNativeHandle = nullptr;
        ContextProperties mProperties = {};

        explicit Context(const ContextProperties& properties);
    public:
        Context(const Context&) = delete;
        Context& operator=(const Context&) = delete;
        Context(Context&& other) noexcept = delete;
        Context& operator=(Context&& other) noexcept = delete;
        ~Context();

        GLFWwindow* GetNativeHandle() const;
        bool IsValidContext() const;
        void SetThisAsCurrentContext() const;
        bool ShouldClose() const;
        void SwapBuffers() const;
        void Update(const Timestep& time);
        ContextProperties& GetProperties();
        const ContextProperties& GetProperties() const;

        static std::weak_ptr<Context> Create(const ContextProperties& properties = {});
        static void SetCurrentContext(const Context& context);
        static std::weak_ptr<Context> GetCurrentContext();
        static ContextMap& GetContexts();
        static void PollEvents();
        static void OnError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
    };
}
