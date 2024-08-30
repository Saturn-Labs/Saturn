#pragma once

namespace Saturn {
    class GLFWManager {
    public:
        static void Initialize();
        static void Terminate();
        static void PollEvents();
    };
}
