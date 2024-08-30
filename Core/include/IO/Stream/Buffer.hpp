#pragma once
#include "Common/Types.hpp"

namespace Saturn {
    class Buffer {
        Byte* m_Data;
        UInt64 m_Size;
        bool m_OwnData;

    public:
        Buffer() = delete;
        Buffer(const Buffer&) = delete;
        Buffer(Buffer&&) = default;
        Buffer& operator=(const Buffer&) = delete;
        Buffer& operator=(Buffer&&) = delete;

        explicit Buffer(UInt64 size);
        Buffer(Byte* data, UInt64 size, bool copyData = false);
        ~Buffer();

        void Resize(UInt64 newSize);
        void Reset();
        UInt64 GetSize() const;
        void* GetData() const;

        Byte* Read(UInt64 position = 0) const;
        void Write(const Byte* data, UInt64 size, UInt64 position = 0);
    };
}
