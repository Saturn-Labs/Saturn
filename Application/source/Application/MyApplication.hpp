#pragma once
#include "imgui.h"
#include "Core/Application.hpp"
#include "Core/Timestep.hpp"
#include "Core/Window.hpp"
#include "Core/LayerSystem/Layer.hpp"
#include "Core/LayerSystem/LayerStack.hpp"
#include "IO/Logger.hpp"
#include "glad/glad.h"

class MyLayer final : public Saturn::Layer {
    Saturn::Logger& logger;
public:
    explicit MyLayer(Saturn::LayerStack &stack) :
        Layer(stack, "MyLayer"),
        logger(stack.GetWindow().GetApplication().GetLogger())
    {
        logger.Info("MyLayer constructed!");
    }

    void OnStart() override {
        logger.Info("MyLayer started!");
    }

    void OnUpdate(Saturn::Timestep timestep) override {
        ImGui::ShowDemoWindow();
        glClearColor(0, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    ~MyLayer() override {
        logger.Info("MyLayer destructed!");
    }
};

class MyApplication final : public Saturn::Application {
public:
    MyApplication();
    ~MyApplication() override;
    void Start() override;
    void Update(Saturn::Timestep deltaTime) override;
};