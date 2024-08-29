#include <iostream>

#include "Core/Framework.hpp"
#include "Core/Window.hpp"

using namespace Saturn;
int main() {
    Framework::Initialize();
    if (Framework::IsInitialized()) {
        Window& window = Framework::GetWindow();
        window.Run();
    }
    return 0;
}
