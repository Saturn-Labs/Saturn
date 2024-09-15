#include "pch.hpp"
#include "Saturn.hpp"
#include "glad/../../src/gl.c"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#undef STB_IMAGE_WRITE_IMPLEMENTATION
#include "Core/Application.hpp"
#include "Core/Logger.hpp"
#include "Core/Rendering/Renderer.hpp"
#include "Core/Resource/ResourceManager.hpp"

namespace Saturn {
    Application* Framework::sApplication = nullptr;
    ResourceManager* Framework::sResourceManager = nullptr;
    bool Framework::sInitialized = false;

    void Framework::Initialize() {
        if (sInitialized)
            return;
        sInitialized = true;
        stbi_set_flip_vertically_on_load(true);
        Logger::Initialize(LOGGER_NAME);
        Renderer::Initialize();
        sResourceManager = new ResourceManager();
        sApplication = CreateApplication();
    }

    void Framework::Shutdown() {
        if (!sInitialized)
            return;
        sInitialized = false;
        delete sApplication;
        delete sResourceManager;
        Renderer::Shutdown();
        Logger::Shutdown();
    }

    Application* Framework::GetApplication() {
        return sApplication;
    }

    ResourceManager* Framework::GetResourceManager() {
        return sResourceManager;
    }
}
