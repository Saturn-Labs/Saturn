#include "Core/Rendering/Buffer/IndexBuffer.hpp"

namespace Saturn {
    IndexBuffer::IndexBuffer(const UInt32* indices, UIntPtr count, BufferUsageHint usageHint) :
        mCount(count) {
        glGenBuffers(1, &mIdentifier);
        if (indices)
            SetIndices(indices, count, usageHint);
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept :
        mIdentifier(std::exchange(other.mIdentifier, 0)),
        mCount(std::exchange(other.mCount, 0)) {
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept {
        if (this != &other) {
            mIdentifier = std::exchange(other.mIdentifier, 0);
            mCount = std::exchange(other.mCount, 0);
        }
        return *this;
    }

    IndexBuffer::~IndexBuffer() {
        if (!IsValid())
            return;
        glDeleteBuffers(1, &mIdentifier);
        mIdentifier = 0;
    }

    void IndexBuffer::Bind() const {
        if (!IsValid())
            return;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIdentifier);
    }

    void IndexBuffer::SetIndices(const UInt32* indices, UIntPtr count, BufferUsageHint usageHint) {
        if (!IsValid())
            return;
        mCount = count;
        const UInt32 oldIndexBuffer = GetCurrent();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIdentifier);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(UInt32), indices, static_cast<GLenum>(usageHint));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldIndexBuffer);
    }

    UInt32 IndexBuffer::GetIdentifier() const {
        return mIdentifier;
    }

    bool IndexBuffer::IsValid() const {
        return mIdentifier != 0 && mCount != 0;
    }

    UIntPtr IndexBuffer::GetCount() const {
        return mCount;
    }

    void IndexBuffer::ResetSlot() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    UInt32 IndexBuffer::GetCurrent() {
        Int32 currentIndexBuffer = 0;
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentIndexBuffer);
        return static_cast<UInt32>(currentIndexBuffer);
    }
}
