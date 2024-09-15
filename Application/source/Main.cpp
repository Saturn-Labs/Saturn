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
#include "Core/Resource/Shader.hpp"
#include "Core/Resource/TextureResource.hpp"
#include "GLFW/glfw3.h"


namespace Saturn {
    class TestApplication final : public Application {
        std::weak_ptr<Context> mainWindow;
        std::shared_ptr<Shader> spritesShader;
        std::shared_ptr<TextureResource> textureResource;
        std::shared_ptr<VertexBuffer<BasicVertex>> vertexBuffer;
        std::shared_ptr<ElementBuffer<UInt32>> elementBuffer;
        VertexArray vertexArray;
        Texture protoTexture;
    public:
        explicit TestApplication() {
            mainWindow = Context::Create({ false, { "Window 1", 640, 480, FrameSync::Vertical }});
            mainWindow.lock()->SetThisAsCurrentContext();


            ResourceManager& resources = *Framework::GetResourceManager();
            const ResourceLocation shaderLocation({
                {"vertex", "assets/shaders/sprites.vert"},
                {"fragment", "assets/shaders/sprites.frag"}
            });
            spritesShader = resources.LoadResource<Shader>(shaderLocation);
            textureResource = resources.LoadResource<TextureResource>({"assets/textures/prototype.png"});

            if (!spritesShader->WaitUntilLoaded() && spritesShader->GetState() == ResourceState::Failed)
                Logger::Error("{}", spritesShader->GetException()->what());
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
            spritesShader->Lock();
            const UInt32 texture = glGetUniformLocation(spritesShader->GetName(), "uTexture");
            glUniform1i(texture, 0);
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