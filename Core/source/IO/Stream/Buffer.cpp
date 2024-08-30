#include "IO/Stream/Buffer.hpp"

namespace Saturn {
    Buffer::Buffer(UInt64 size) :
        m_Data(new Byte[size]),
        m_Size(size),
        m_OwnData(true)
    {
    }

    Buffer::Buffer(Byte* data, UInt64 size, bool copyData) :
        m_Size(size),
        m_OwnData(copyData)
    {
        if (copyData) {
            m_Data = new Byte[size];
            std::memcpy(m_Data, data, size);
        }
        else {
            m_Data = data;
        }
    }

    Buffer::~Buffer() {
        if (m_OwnData)
            delete[] m_Data;
    }

    void Buffer::Resize(UInt64 newSize) {
        if (newSize <= m_Size)
            throw std::exception("Failed to resize buffer, the specified new size was less than or equal to the current size.");

        if (!m_OwnData)
            throw std::exception("Failed to resize buffer, the buffer does not own its data.");

        auto* newData = new Byte[newSize];
        std::memcpy(newData, m_Data, m_Size);
        delete[] m_Data;
        m_Data = newData;
        m_Size = newSize;
    }

    void Buffer::Reset() {
        if (!m_OwnData)
            throw std::exception("Failed to reset buffer, the buffer does not own its data.");

        std::memset(m_Data, 0, m_Size);
    }

    UInt64 Buffer::GetSize() const {
        return m_Size;
    }

    void* Buffer::GetData() const {
        return m_Data;
    }

    Byte* Buffer::Read(UInt64 position) const {
        if (position >= m_Size)
            throw std::exception("Failed to read from buffer, the specified position exceeds the current buffer size.");

        return m_Data + position;
    }

    void Buffer::Write(const Byte* data, UInt64 size, UInt64 position) {
        if (position + size > m_Size)
            throw std::exception("Failed to write to buffer, the specified (position + size) exceeds the current buffer size.");

        std::memcpy(m_Data + position, data, size);
    }
}
