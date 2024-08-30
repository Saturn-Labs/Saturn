#include "Core/LayerSystem/Layer.hpp"

#include "Core/Timestep.hpp"
#include "Utils/UUIDGenerator.hpp"

namespace Saturn {
    Layer::Layer(LayerStack &stack, const String &name) :
        m_Stack(stack),
        m_Name(name),
        m_Identifier(UUIDGenerator::GenerateUUID()) {}
    void Layer::OnStart() {}
    void Layer::OnUpdate(Timestep timestep) {}
    void Layer::OnEnable() {}
    void Layer::OnDisable() {}
    Layer::~Layer() = default;
}
