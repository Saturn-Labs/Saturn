#include <iostream>

#include "Core/Framework.hpp"
#include "Core/Timestep.hpp"
#include "Core/Window.hpp"
#include "glm/glm.hpp"
#include "IO/File.hpp"

using namespace Saturn;

class MyLayer final : public Layer {
public:
    MyLayer(LayerStack &stack, Logger& logger, Renderer& renderer, const String &name) :
        Layer(stack, logger, renderer, name)
    {
    }

    void Awake() override {

    }

    void Update(const Timestep &timestep) override {

    }

    ~MyLayer() override {

    }
};

int main() {
    Framework::Initialize();
    if (Framework::IsInitialized()) {
        Logger& logger = Framework::GetLogger();
        Window& window = Framework::GetWindow();
        LayerStack& layers = Framework::GetLayerStack();

        MyLayer& layer = layers.Emplace<MyLayer>("MyLayer");
        window.Run();
        layers.Remove(layer);

        Framework::Shutdown();
    }
    return 0;
}
