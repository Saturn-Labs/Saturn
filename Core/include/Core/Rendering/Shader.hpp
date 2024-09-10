#pragma once
#include "Common/Types.hpp"

namespace Saturn {
    struct ShaderSource {
        String Vertex;
        String Fragment;
    };

    class Shader {
        UInt32 mIdentifier = 0;
    public:
        explicit Shader(const ShaderSource& source);

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        ~Shader();
        void Use() const;
        UInt32 GetIdentifier() const;
        bool IsValid() const;
        static void ResetSlot();
        static UInt32 GetCurrent();
    };
}
