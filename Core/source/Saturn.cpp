#include "Saturn.hpp"
#include "glad/../../src/gl.c"
#include "glad/gl.h"

namespace Saturn {
    Application* Framework::sCurrentApplication = nullptr;
    Application* Framework::GetCurrentApplication() {
        return sCurrentApplication;
    }
}