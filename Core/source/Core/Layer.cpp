#include "Core/Layer.hpp"

#include "Core/LayerStack.hpp"
#include "Utils/UUIDGenerator.hpp"

namespace Saturn {
    Layer::Layer(LayerStack& stack, Logger& logger, Renderer& renderer, const String &name) :
        m_LayerStack(stack),
        m_Identifier(UUIDGenerator::GenerateUUID()),
        m_Name(name),
        logger(logger),
        renderer(renderer)
    {
    }

    Layer::~Layer() = default;
    void Layer::Awake() {}
    void Layer::Update(const Timestep& timestep) {}
}