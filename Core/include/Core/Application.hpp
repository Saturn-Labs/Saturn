#pragma once
#include "Common/Timestep.hpp"

namespace Saturn {
    class Context;
    class Application {
        double mTimeNow = 0;
        double mLastTime = 0;
    public:
        explicit Application();
        virtual ~Application();
        virtual void Run();
        virtual void Update(const Timestep& time) = 0;
    };
}
