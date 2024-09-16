#include <glad/gl.h>
#include <iostream>
#include <stb_image_write.h>

#include "Core/Context.hpp"
#include "Core/Entry.hpp"
#include "Core/Logger.hpp"
#include "Core/Rendering/BasicVertex.hpp"
#include "Core/Rendering/Buffer/ElementBuffer.hpp"
#include "Core/Rendering/Buffer/VertexBuffer.hpp"
#include "Core/Rendering/Texture.hpp"
#include "Core/Rendering/VertexArray.hpp"
#include "Core/Resource/ResourceLocation.hpp"
#include "Core/Resource/ResourceManager.hpp"
#include "Core/Rendering/Shader/Shader.hpp"
#include "Core/Resource/ShaderResource.hpp"
#include "Core/Resource/TextureResource.hpp"
#include "GLFW/glfw3.h"


namespace Saturn {
    class TestApplication final : public Application {
        std::weak_ptr<Context> mainWindow;
        std::shared_ptr<ShaderResource> spritesShaderResource;
        std::shared_ptr<TextureResource> textureResource;
        std::shared_ptr<VertexBuffer<BasicVertex>> vertexBuffer;
        std::shared_ptr<ElementBuffer<UInt32>> elementBuffer;
        VertexArray vertexArray;
        Texture protoTexture;
        std::shared_ptr<Shader> spritesShader;
    public:
        explicit TestApplication() {
            mainWindow = Context::Create({ false, { "Window 1", 640, 480, FrameSync::Vertical }});
            mainWindow.lock()->SetThisAsCurrentContext();


            ResourceManager& resources = *Framework::GetResourceManager();
            const ResourceLocation shaderLocation({
                {"vertex", "assets/shaders/sprites.vert"},
                {"fragment", "assets/shaders/sprites.frag"}
            });
            spritesShaderResource = resources.LoadResource<ShaderResource>(shaderLocation);
            textureResource = resources.LoadResource<TextureResource>({"assets/textures/prototype.png"});

            if (!spritesShaderResource->WaitUntilLoaded() && spritesShaderResource->GetState() == ResourceState::Failed)
                Logger::Error("{}", spritesShaderResource->GetException()->what());
            spritesShader = spritesShaderResource->GetShader();

            if (!textureResource->WaitUntilLoaded() && textureResource->GetState() == ResourceState::Failed)
                Logger::Error("{}", textureResource->GetException()->what());

            protoTexture = Texture(textureResource->GetTextureData());
            protoTexture.Lock(0);

            vertexBuffer = VertexBuffer<BasicVertex>::Create({
                {{ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f }},
                {{  0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f }},
                {{  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f }},
                {{ -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f }},
            });

            elementBuffer = ElementBuffer<UInt32>::Create({
                0, 1, 2, 2, 3, 0
            });

            vertexArray = std::move(VertexArray(vertexBuffer, elementBuffer));
            vertexArray.SetLayout(BasicVertex::GetLayout());
            vertexArray.Lock();
            spritesShader->AddUniform<int>("uTexture", 0);
            spritesShader->UpdateData();
            spritesShader->Lock();
        }

        void Update(const Timestep& time) override {
            if (const auto window = mainWindow.lock()) {
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                glDrawElements(GL_TRIANGLES, elementBuffer->GetElementCount(), GL_UNSIGNED_INT, nullptr);
            }
        }
    };
}

Saturn::Application* Saturn::CreateApplication() {
    return new TestApplication();
}