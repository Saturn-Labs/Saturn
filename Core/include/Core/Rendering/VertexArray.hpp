#pragma once
#include "Buffer/IndexBuffer.hpp"
#include "Buffer/VertexBuffer.hpp"
#include "Common/Types.hpp"
#include "Utils/GLTypeHelper.hpp"

namespace Saturn {
    class VertexArray {
        UInt32 mIdentifier = 0;
        VertexBuffer mVertexBuffer;
        IndexBuffer mIndexBuffer;
    public:
        VertexArray();
        VertexArray(VertexBuffer&& vertexBuffer, IndexBuffer&& indexBuffer);

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        VertexArray(VertexArray&& other) noexcept;
        VertexArray& operator=(VertexArray&& other) noexcept;

        ~VertexArray();
        void Bind() const;
        UInt32 GetIdentifier() const;
        bool IsValid() const;
        bool IsVertexBufferValid() const;
        bool IsIndexBufferValid() const;
        VertexBuffer& GetVertexBuffer();
        IndexBuffer& GetIndexBuffer();
        void SetVertexBuffer(VertexBuffer&& vertexBuffer);
        void SetIndexBuffer(IndexBuffer&& indexBuffer);
        void RebindBuffers() const;
        void RebindBuffers(VertexBuffer&& vertexBuffer, IndexBuffer&& indexBuffer);

        template<typename T>
        void SetVertexAttribute(UInt16 index, UInt32 count, bool normalized, UIntPtr stride, UIntPtr offset) const {
            if (!IsValid() || !IsVertexBufferValid())
                return;
            constexpr GLenum type = GLTypeHelper::GetGLTypeForT<T>();
            const UInt32 oldVertexArray = GetCurrent();
            Bind();
            const UInt32 oldVertexBuffer = VertexBuffer::GetCurrent();
            mVertexBuffer.Bind();
            glVertexAttribPointer(index, count, type, normalized, stride, reinterpret_cast<const GLvoid*>(offset));
            glEnableVertexAttribArray(index);
            ResetSlot();
            glBindBuffer(GL_ARRAY_BUFFER, oldVertexBuffer);
            glBindVertexArray(oldVertexArray);
        }

        static void ResetSlot();
        static UInt32 GetCurrent();
    };
}
