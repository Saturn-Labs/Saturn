#pragma once
#include <vector>

#include "Layer.hpp"
#include "Common/Types.hpp"

namespace Saturn {
    class LayerStack {
        Vector<Unique<Layer>> m_Layers = {};

    private:
        LayerStack() = default;

    public:
        LayerStack(const LayerStack&) = delete;
        LayerStack(LayerStack&&) = delete;
        LayerStack& operator=(const LayerStack&) = delete;
        LayerStack& operator=(LayerStack&&) = delete;

        static LayerStack* Create();

    public:
        template<typename TLayer = Layer, typename... Args>
        TLayer& Emplace(Args&&... args) {
            return static_cast<TLayer&>(*m_Layers.emplace_back(CreateUnique<TLayer>(*this, std::forward<Args>(args)...)));
        }

        template<typename TLayer = Layer>
        void Remove(TLayer& layer) {
            auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [&layer](const Unique<Layer>& ptr) {
                return ptr->GetIdentifier() == layer.GetIdentifier();
            });

            if (it != m_Layers.end())
                m_Layers.erase(it);
        }

        template<typename TLayer = Layer>
        Nullable<TLayer&> FindLayer(const String& name) {
            auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [&name](const Unique<Layer>& value) {
               return value->GetName() == name;
            });

            if (it == m_Layers.end())
                return null;

            return *it->get();
        }

        template<typename TLayer = Layer>
        Nullable<TLayer&> FindLayer(const UUID& name) {
            auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [&name](const Unique<Layer>& value) {
               return value->GetIdentifier() == name;
            });

            if (it == m_Layers.end())
                return null;

            return *it->get();
        }

        void Update(const Timestep& timestep) const;

        const Vector<Unique<Layer>>& GetLayers() const {
            return m_Layers;
        }

        Vector<Unique<Layer>>& GetLayers() {
            return m_Layers;
        }
    };
}
