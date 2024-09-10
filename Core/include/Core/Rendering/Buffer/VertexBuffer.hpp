#pragma once
#include "BufferUsagePattern.hpp"
#include "Common/Types.hpp"

namespace Saturn {
    class VertexBuffer {
        UInt32 mIdentifier = 0;
    public:
        VertexBuffer() = default;

        VertexBuffer(const void* data, UIntPtr size, BufferUsageHint usageHint = BufferUsageHint::StaticDraw);

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer(VertexBuffer&& other) noexcept;
        VertexBuffer& operator=(VertexBuffer&& other) noexcept;

        ~VertexBuffer();
        void Bind() const;
        void SetData(const void* data, UIntPtr size, BufferUsageHint usageHint = BufferUsageHint::StaticDraw) const;
        UInt32 GetIdentifier() const;
        bool IsValid() const;
        static void ResetSlot();
        static UInt32 GetCurrent();
    };
}
