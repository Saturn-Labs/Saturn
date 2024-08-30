#pragma once
#include "Common/Types.hpp"

namespace Saturn {
    struct Timestep;
    class LayerStack;
    class Layer {
        friend class LayerStack;
        LayerStack& m_Stack;
        String m_Name;
        String m_Identifier;
        bool m_IsAwake = false;
        bool m_IsActive = true;

    public:
        Layer() = delete;
        Layer(const Layer&) = delete;
        Layer(Layer&&) = delete;
        Layer& operator=(const Layer&) = delete;
        Layer& operator=(Layer&&) = delete;
        Layer(LayerStack& stack, const String& name);
        virtual void OnStart();
        virtual void OnUpdate(Timestep timestep);
        virtual void OnEnable();
        virtual void OnDisable();
        virtual ~Layer();

        bool IsAwake() const {
            return m_IsAwake;
        }

        bool IsEnabled() const {
            return m_IsActive;
        }

        void SetActive(bool active) {
            m_IsActive = active;
            active ? OnEnable() : OnDisable();
        }
    };
}
