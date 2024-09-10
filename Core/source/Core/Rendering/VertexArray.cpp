#include "Core/Rendering/VertexArray.hpp"

namespace Saturn {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &mIdentifier);
    }

    VertexArray::VertexArray(VertexBuffer&& vertexBuffer, IndexBuffer&& indexBuffer) :
        mVertexBuffer(std::move(vertexBuffer)),
        mIndexBuffer(std::move(indexBuffer)) {
        glGenVertexArrays(1, &mIdentifier);
        const UInt32 oldVertexArray = GetCurrent();
        const UInt32 oldVertexBuffer = VertexBuffer::GetCurrent();
        const UInt32 oldIndexBuffer = IndexBuffer::GetCurrent();
        glBindVertexArray(mIdentifier);
        mVertexBuffer.Bind();
        mIndexBuffer.Bind();
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, oldVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldIndexBuffer);
        glBindVertexArray(oldVertexArray);
    }

    VertexArray::VertexArray(VertexArray&& other) noexcept :
        mIdentifier(std::exchange(other.mIdentifier, 0)) {
    }

    VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
        if (this != &other)
            mIdentifier = std::exchange(other.mIdentifier, 0);
        return *this;
    }

    VertexArray::~VertexArray() {
        if (!IsValid())
            return;
        glDeleteVertexArrays(1, &mIdentifier);
    }

    void VertexArray::Bind() const {
        if (!IsValid())
            return;
        glBindVertexArray(mIdentifier);
    }

    UInt32 VertexArray::GetIdentifier() const {
        return mIdentifier;
    }

    bool VertexArray::IsValid() const {
        return mIdentifier != 0;
    }

    bool VertexArray::IsVertexBufferValid() const {
        return mVertexBuffer.IsValid();
    }

    bool VertexArray::IsIndexBufferValid() const {
        return mIndexBuffer.IsValid();
    }

    VertexBuffer& VertexArray::GetVertexBuffer() {
        return mVertexBuffer;
    }

    IndexBuffer& VertexArray::GetIndexBuffer() {
        return mIndexBuffer;
    }

    void VertexArray::SetVertexBuffer(VertexBuffer&& vertexBuffer) {
        if (!IsValid())
            return;
        mVertexBuffer = std::move(vertexBuffer);
        RebindBuffers();
    }

    void VertexArray::SetIndexBuffer(IndexBuffer&& indexBuffer) {
        if (!IsValid())
            return;
        mIndexBuffer = std::move(indexBuffer);
        RebindBuffers();
    }

    void VertexArray::RebindBuffers() const {
        if (!IsValid())
            return;
        const UInt32 oldVertexArray = GetCurrent();
        const UInt32 oldVertexBuffer = VertexBuffer::GetCurrent();
        const UInt32 oldIndexBuffer = IndexBuffer::GetCurrent();
        glBindVertexArray(mIdentifier);
        mVertexBuffer.Bind();
        mIndexBuffer.Bind();
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, oldVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldIndexBuffer);
        glBindVertexArray(oldVertexArray);
    }

    void VertexArray::RebindBuffers(VertexBuffer&& vertexBuffer, IndexBuffer&& indexBuffer) {
        if (!IsValid())
            return;
        const UInt32 oldVertexArray = GetCurrent();
        const UInt32 oldVertexBuffer = VertexBuffer::GetCurrent();
        const UInt32 oldIndexBuffer = IndexBuffer::GetCurrent();
        glBindVertexArray(mIdentifier);
        mVertexBuffer = std::move(vertexBuffer);
        mVertexBuffer.Bind();
        mIndexBuffer = std::move(indexBuffer);
        mIndexBuffer.Bind();
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, oldVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldIndexBuffer);
        glBindVertexArray(oldVertexArray);
    }

    void VertexArray::ResetSlot() {
        glBindVertexArray(0);
    }

    UInt32 VertexArray::GetCurrent() {
        Int32 currentVertexArray = 0;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVertexArray);
        return static_cast<UInt32>(currentVertexArray);
    }
}
