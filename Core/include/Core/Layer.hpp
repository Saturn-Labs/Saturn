#pragma once
#include "uuid_v4.h"
#include "Common/Types.hpp"

using namespace UUIDv4;
namespace Saturn {
    struct Timestep;
    class LayerStack;
    class Layer {
        friend class LayerStack;
    protected:
        LayerStack& m_LayerStack;
        UUID m_Identifier;
        String m_Name;
        bool m_IsAwaken = false;
    public:
        explicit Layer(LayerStack& stack, const String& name);
        Layer(const Layer&) = delete;
        Layer(Layer&&) = delete;
        Layer& operator=(const Layer&) = delete;
        Layer& operator=(Layer&&) = delete;
        virtual ~Layer();

    public:
        virtual void Awake();
        virtual void Update(const Timestep& timestep);

    public:
        String GetName() const {
            return m_Name;
        }

        const UUID& GetIdentifier() const {
            return m_Identifier;
        }

        LayerStack& GetLayerStack() const {
            return m_LayerStack;
        }

        bool IsAwaken() const {
            return m_IsAwaken;
        }
    };
}