#pragma once
#include "LayerStack.hpp"
#include "Window.hpp"
#include "Common/Types.hpp"
#include "IO/Logger.hpp"

namespace Saturn {
    class Framework {
    private:
        static std::atomic<bool> s_Initialized;
        static Window* s_Window;
        static Logger* s_Logger;
        static LayerStack* s_LayerStack;

    public:
        Framework() = delete;
        Framework(const Framework&) = delete;
        Framework(Framework&&) = delete;
        Framework& operator=(const Framework&) = delete;
        Framework& operator=(Framework&&) = delete;

        static bool Initialize(const LoggerProperties& loggerProps = {}, const WindowProperties& windowProps = {});
        static bool Shutdown();

        static bool IsInitialized() {
            return s_Initialized;
        }

        static bool HasWindow() {
            return IsInitialized() && s_Window;
        }
        static Window& GetWindow() {
            return *s_Window;
        }

        static bool HasLogger() {
            return IsInitialized() && s_Logger;
        }
        static Logger& GetLogger() {
            return *s_Logger;
        }

        static bool HasLayerStack() {
            return IsInitialized() && s_LayerStack;
        }
        static LayerStack& GetLayerStack() {
            return *s_LayerStack;
        }
    };
}
