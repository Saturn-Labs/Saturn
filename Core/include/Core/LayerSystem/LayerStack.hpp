#pragma once
#include <map>
#include "Layer.hpp"
#include "Common/Types.hpp"

namespace Saturn {
    class Window;

    class LayerStack {
        Window& m_Window;
        Shared<Layer> m_BaseLayer;
        std::map<String, Shared<Layer>> m_Layers = {};

    public:
        LayerStack() = delete;
        LayerStack(const LayerStack&) = delete;
        LayerStack(LayerStack&&) noexcept = delete;
        LayerStack& operator=(const LayerStack&) = delete;
        LayerStack& operator=(LayerStack&&) noexcept = delete;

        explicit LayerStack(Window& window);
        ~LayerStack();

        bool HasBaseLayer() const {
            return m_BaseLayer != nullptr;
        }

        Layer& GetBaseLayer() const {
            return *m_BaseLayer;
        }

        template<typename TLayer = Layer, typename... Args>
        TLayer& SetBaseLayer(Args&&... layerArgs) {
            return static_cast<TLayer&>(*(m_BaseLayer = CreateShared<TLayer>(*this, std::forward<Args>(layerArgs)...)));
        }

        template<typename TLayer = Layer, typename... Args>
        TLayer& AddLayer(Args&&... layerArgs) {
            auto layer = CreateShared<TLayer>(*this, std::forward<Args>(layerArgs)...);
            m_Layers[layer->GetIdentifier()] = layer;
            return *layer;
        }

        void RemoveLayer(const String& layerIdentifier);
        Layer& GetLayer(const String& layerIdentifier);
        void Update(Timestep timestep);
        const Window& GetWindow() const;
        Window& GetWindow();
    };
}
