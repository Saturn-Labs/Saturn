#include <iostream>
#include <glad/gl.h>

#include "Core/Entry.hpp"
#include "Core/Logger.hpp"
#include "Core/Content/DeferredContent.hpp"
#include "Core/Content/ShaderContent.hpp"
#include "Core/Rendering/VertexArray.hpp"
#include "Core/Rendering/Buffer/VertexBuffer.hpp"
#include "GLFW/glfw3.h"

namespace Saturn {
    class TestApplication final : public Application {
    public:
        explicit TestApplication() : Application({ .LoggerName = "TestApplication" }) {

        }

        void Run() override {
            if (!glfwInit())
                return;

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            auto* window = glfwCreateWindow(640, 480, "Default Window", nullptr, nullptr);
            if (!window) {
                glfwTerminate();
                return;
            }

            glfwMakeContextCurrent(window);
            int version = gladLoadGL(glfwGetProcAddress);
            if (version == 0) {
                printf("Failed to initialize OpenGL context\n");
                return;
            }

            mLogger.Info("OpenGL Version: {}", (const char*)glGetString(GL_VERSION));

            const Shared<ShaderContent> shaderContent = mContentManager.LoadContent<ShaderContent>({
                { "vert", "shaders/sprites.vert" },
                { "frag", "shaders/sprites.frag" }
            });
            shaderContent->WaitUntilLoaded();
            mLogger.Info("Shader asset loaded!");

            float data[] = {
                -0.5f,  0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
                 0.5f,  0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f,
                 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f,
                -0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f
            };

            UInt32 indices[] = {
                0, 1, 2, 2, 3, 0
            };

            VertexArray vertexArray;
            VertexBuffer vertexBuffer(data, sizeof(data));
            IndexBuffer indexBuffer(indices, sizeof(indices) / sizeof(UInt32));
            vertexArray.SetVertexBuffer(std::move(vertexBuffer));
            vertexArray.SetIndexBuffer(std::move(indexBuffer));
            vertexArray.SetVertexAttribute<float>(0, 3, false, 7 * sizeof(float), 0);
            vertexArray.SetVertexAttribute<float>(1, 4, false, 7 * sizeof(float), 3 * sizeof(float));
            vertexArray.Bind();

            const auto shader = shaderContent->Compile();
            shader->Use();


            while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                glDrawElements(GL_TRIANGLES, vertexArray.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
                int err = glGetError();
                while (err != 0) {
                    mLogger.Error("OpenGL Error: {}", err);
                    err = glGetError();
                }

                glfwSwapBuffers(window);
            }
            glfwTerminate();
        }
    };
}

Saturn::Application* Saturn::CreateApplication()
{
    return new TestApplication();
}
