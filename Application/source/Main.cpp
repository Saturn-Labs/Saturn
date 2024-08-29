#include <iostream>
#include "Core/Window.hpp"

using namespace Saturn;
int main() {
    auto* window = Window::CreateWindow();
    window->Run();
    return 0;
}
