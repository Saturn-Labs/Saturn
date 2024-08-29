#include <iostream>

#include "Core/Framework.hpp"
#include "Core/Timestep.hpp"
#include "Core/Window.hpp"

using namespace Saturn;

class MyLayer final : public Layer {
public:
    Logger& logger;

    MyLayer(LayerStack &stack, const String &name) :
        Layer(stack, name),
        logger(Framework::GetLogger())
    {
        logger.Info("MyLayer created!");
    }

    void Awake() override {
        logger.Trace("MyLayer awake!");
    }

    void Update(const Timestep &timestep) override {
        logger.Trace("MyLayer update: {}s", timestep.Delta);
    }

    ~MyLayer() override {
        logger.Info("MyLayer destroyed!");
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
