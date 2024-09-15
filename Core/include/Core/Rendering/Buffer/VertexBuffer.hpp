#pragma once
#include "BufferUsagePattern.hpp"
#include "Common/Types.hpp"
#include "Core/Rendering/LockableResource.hpp"

namespace Saturn {
    template<typename TVertex>
    class VertexBuffer final : public LockableResource<UInt32, 0> {
        std::vector<TVertex> mVertices = {};
    public:
        explicit VertexBuffer(const std::vector<TVertex>& vertices, BufferUsageHint usageHint = BufferUsageHint::StaticDraw) :
            mVertices(vertices) {
            SetVertices(vertices, usageHint);
        }

        ~VertexBuffer() noexcept override {
            if (!VertexBuffer::IsValid())
                return;
            glDeleteBuffers(1, &mName);
        }

        VertexBuffer(VertexBuffer&& other) noexcept = delete;
        VertexBuffer& operator=(VertexBuffer&& other) noexcept = delete;
        VertexBuffer(const VertexBuffer& other) = delete;
        VertexBuffer& operator=(const VertexBuffer& other) noexcept = delete;

        void SetVertices(const std::vector<TVertex>& vertices, BufferUsageHint usageHint = BufferUsageHint::StaticDraw) {
            if (!IsValid()) {
                glGenBuffers(1, &mName);
            }
            const UInt32 lastCurrent = GetCurrent();
            Lock();
            mVertices = vertices;
            glBufferData(GL_ARRAY_BUFFER, sizeof(TVertex) * mVertices.size(), mVertices.data(), static_cast<GLenum>(usageHint));
            glBindBuffer(GL_ARRAY_BUFFER, lastCurrent);
        }

        static void SetCurrent(UInt32 mId) {
            glBindBuffer(GL_ARRAY_BUFFER, mId);
        }

        static UInt32 GetCurrent() {
            Int32 current = 0;
            glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &current);
            return static_cast<UInt32>(current);
        }

        UInt32 GetVerticesCount() const {
            return mVertices.size();
        }

        static std::shared_ptr<VertexBuffer> Create(const std::vector<TVertex> &vertices, BufferUsageHint usageHint = BufferUsageHint::StaticDraw) {
            return std::make_shared<VertexBuffer>(vertices, usageHint);
        }

        void Lock() override {
            if (!IsValid())
                return;
            glBindBuffer(GL_ARRAY_BUFFER, mName);
        }

        void Unlock() override {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    };
}