#pragma once
#include <glad/gl.h>

#include "Common/Types.hpp"

namespace Saturn {
    enum class BufferUsage : UInt32 {
        Stream  = 0x88E0,  // Base for Stream usage (0x88E0)
        Static  = 0x88E4,  // Base for Static usage (0x88E4)
        Dynamic = 0x88E8   // Base for Dynamic usage (0x88E8)
    };

    enum class BufferAccess : UInt32 {
        Draw = 0x00,  // Offset 0 for Draw
        Read = 0x01,  // Offset 1 for Read
        Copy = 0x02   // Offset 2 for Copy
    };

    enum class BufferUsageHint : UInt32 {
        StreamCopy = 0x88E2,
        StreamDraw = 0x88E0,
        StreamRead = 0x88E1,
        StaticCopy = 0x88E6,
        StaticDraw = 0x88E4,
        StaticRead = 0x88E5,
        DynamicCopy = 0x88EA,
        DynamicDraw = 0x88E8,
        DynamicRead = 0x88E9
    };

    constexpr BufferUsageHint operator|(BufferUsage usage, BufferAccess access) {
        return static_cast<BufferUsageHint>(static_cast<uint32_t>(usage) + static_cast<uint32_t>(access));
    }
}
