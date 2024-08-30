#include "Core/LayerStack.hpp"

#include "Core/Framework.hpp"

namespace Saturn {
    LayerStack::LayerStack(Logger &logger, Renderer& renderer) :
        logger(logger),
        m_Renderer(renderer)
    {
    }

    LayerStack* LayerStack::Create(Logger& logger, Renderer& renderer) {
        if (Framework::HasLayerStack())
            return &Framework::GetLayerStack();

        return new LayerStack(logger, renderer);
    }

    void LayerStack::Update(const Timestep& timestep) const {
        for (const Unique<Layer>& layer : m_Layers) {
            if (!layer->IsAwaken()) {
                layer->m_IsAwaken = true;
                layer->Awake();
            }
            layer->Update(timestep);
        }
    }
}
