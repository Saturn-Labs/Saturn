#include "Core/Rendering/Buffer/VertexBuffer.hpp"

namespace Saturn {
    VertexBuffer::VertexBuffer(const void* data, UIntPtr size, BufferUsageHint usageHint) {
        glGenBuffers(1, &mIdentifier);
        if (data)
            SetData(data, size, usageHint);
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept :
        mIdentifier(std::exchange(other.mIdentifier, 0)) {
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
        if (this != &other)
            mIdentifier = std::exchange(other.mIdentifier, 0);
        return *this;
    }

    VertexBuffer::~VertexBuffer() {
        if (!IsValid())
            return;
        glDeleteBuffers(1, &mIdentifier);
        mIdentifier = 0;
    }

    void VertexBuffer::Bind() const {
        if (!IsValid())
            return;
        glBindBuffer(GL_ARRAY_BUFFER, mIdentifier);
    }

    void VertexBuffer::SetData(const void* data, UIntPtr size, BufferUsageHint usageHint) const {
        if (!IsValid())
            return;
        const UInt32 oldVertexBuffer = GetCurrent();
        glBindBuffer(GL_ARRAY_BUFFER, mIdentifier);
        glBufferData(GL_ARRAY_BUFFER, size, data, static_cast<GLenum>(usageHint));
        glBindBuffer(GL_ARRAY_BUFFER, oldVertexBuffer);
    }

    UInt32 VertexBuffer::GetIdentifier() const {
        return mIdentifier;
    }

    bool VertexBuffer::IsValid() const {
        return mIdentifier != 0;
    }

    void VertexBuffer::ResetSlot() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    UInt32 VertexBuffer::GetCurrent() {
        Int32 currentVertexBuffer = 0;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentVertexBuffer);
        return static_cast<UInt32>(currentVertexBuffer);
    }
}
