#pragma once

namespace Saturn {
    class Framework {
    private:
        Framework() {}
        Framework(const Framework&) = delete;
        Framework& operator=(const Framework&) = delete;
        Framework(Framework&&) = delete;
        Framework& operator=(Framework&&) = delete;

    public:
        static Framework* CreateInstance() {

        }
    };
}