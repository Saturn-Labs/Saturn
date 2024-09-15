#pragma once

namespace Saturn {
    class Renderer {
    public:
        static void Initialize();
        static void Shutdown();
        static void BeginUpdate();
        static void EndUpdate();
    };
}