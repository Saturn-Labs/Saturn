#include "pch.hpp"
#include "Saturn.hpp"
#include "Core/Application.hpp"
#include "Core/Context.hpp"

namespace Saturn {
    Application::Application() {
        if (Framework::GetApplication())
            throw std::exception("Illegal instantiation: Cannot create multiple Application instances!");
    }

    Application::~Application() = default;

    void Application::Run() {
        ContextMap& contexts = Context::GetContexts();
        while (true) {
            if (std::ranges::all_of(contexts, [](const auto& elements) {
                auto ctx = elements.second;
                return ctx->ShouldClose() || ctx->GetProperties().Windowless;
            }) || contexts.empty()) {
                break;
            }

            mTimeNow = glfwGetTime();
            const double dt = static_cast<float>(mTimeNow - mLastTime);
            const Timestep time(dt);
            mLastTime = mTimeNow;

            Update(time);
            ContextMap::iterator contextsIt = contexts.begin();
            while (contextsIt != contexts.end()) {
                const auto ctx = contextsIt->second;
                if (ctx->ShouldClose()) {
                    contextsIt = contexts.erase(contextsIt);
                    continue;
                }

                if (!ctx->GetProperties().Windowless) {
                    ctx->SetThisAsCurrentContext();
                    ctx->Update(time);
                    ctx->SwapBuffers();
                }
                ++contextsIt;
            }
            Context::PollEvents();
        }
    }
}
