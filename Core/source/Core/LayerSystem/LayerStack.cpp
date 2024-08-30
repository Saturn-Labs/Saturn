#include "Core/LayerSystem/LayerStack.hpp"

#include <ranges>

#include "Core/Timestep.hpp"

namespace Saturn {
    LayerStack::LayerStack(Window& window) :
        m_Window(window)
    {
    }

    LayerStack::~LayerStack() {
        m_BaseLayer = nullptr;
        m_Layers.clear();
    }

    void LayerStack::RemoveLayer(const String &layerIdentifier) {
        const auto it = m_Layers.find(layerIdentifier);
        if (it == m_Layers.end())
            return;
        m_Layers.erase(it);
    }

    Layer& LayerStack::GetLayer(const String &layerIdentifier) {
        const auto it = m_Layers.find(layerIdentifier);
        if (it == m_Layers.end())
            throw std::runtime_error("Layer not found: " + layerIdentifier);
        return *it->second;
    }

    void LayerStack::Update(Timestep timestep) {
        if (m_BaseLayer != nullptr) {
            if (!m_BaseLayer->IsAwake()) {
                m_BaseLayer->OnStart();
                m_BaseLayer->m_IsAwake = true;
            }
            else if (m_BaseLayer->IsEnabled()) {
                m_BaseLayer->OnUpdate(timestep);
            }
        }
        for (const auto& layer : m_Layers | std::views::values) {
            if (!layer->IsAwake()) {
                layer->OnStart();
                layer->m_IsAwake = true;
            }
            else if (layer->IsEnabled()) {
                layer->OnUpdate(timestep);
            }
        }
    }

    const Window& LayerStack::GetWindow() const {
        return m_Window;
    }

    Window& LayerStack::GetWindow() {
        return m_Window;
    }
}
