#pragma once
#include "BufferUsagePattern.hpp"
#include "Common/Types.hpp"

namespace Saturn {
    class IndexBuffer {
        UInt32 mIdentifier = 0;
        UIntPtr mCount = 0;
    public:
        IndexBuffer() = default;

        IndexBuffer(const UInt32* indices, UIntPtr count, BufferUsageHint usageHint = BufferUsageHint::StaticDraw);

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(IndexBuffer&& other) noexcept;
        IndexBuffer& operator=(IndexBuffer&& other) noexcept;

        ~IndexBuffer();
        void Bind() const;
        void SetIndices(const UInt32* indices, UIntPtr count, BufferUsageHint usageHint = BufferUsageHint::StaticDraw);
        UInt32 GetIdentifier() const;
        bool IsValid() const;
        UIntPtr GetCount() const;
        static void ResetSlot();
        static UInt32 GetCurrent();
    };
}
