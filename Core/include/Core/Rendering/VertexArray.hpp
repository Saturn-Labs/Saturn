#pragma once
#include "Buffer/ElementBuffer.hpp"
#include "Buffer/VertexBuffer.hpp"
#include "Common/Types.hpp"
#include "LockableResource.hpp"
#include "Utils/GLTypeHelper.hpp"

namespace Saturn {
    class VertexArray final : public LockableResource<UInt32, 0> {
        std::weak_ptr<LockableResource> mVertexBuffer = {};
        std::weak_ptr<LockableResource> mElementBuffer = {};
        VertexAttributeLayout mLayout = VertexAttributeLayout({});
    public:
        VertexArray() {
            glGenVertexArrays(1, &mName);
        }

        explicit VertexArray(const std::weak_ptr<LockableResource>& vertexBuffer, const std::weak_ptr<LockableResource>& elementBuffer) :
            mVertexBuffer(vertexBuffer),
            mElementBuffer(elementBuffer) {
            glGenVertexArrays(1, &mName);
        }

        ~VertexArray() noexcept override {
            if (!VertexArray::IsValid())
                return;
            glDeleteVertexArrays(1, &mName);
        }

        VertexArray(VertexArray&& other) noexcept :
            mVertexBuffer(std::move(other.mVertexBuffer)),
            mElementBuffer(std::move(other.mElementBuffer)),
            mLayout(std::exchange(other.mLayout, VertexAttributeLayout({}))) {
            mName = std::exchange(other.mName, 0);
        }

        VertexArray& operator=(VertexArray&& other) noexcept {
            if (this != &other) {
                mName = std::exchange(other.mName, 0);
                mVertexBuffer = std::move(other.mVertexBuffer);
                mElementBuffer = std::move(other.mElementBuffer);
                mLayout = std::exchange(other.mLayout, VertexAttributeLayout({}));
            }
            return *this;
        };

        VertexArray(const VertexArray& other) = delete;
        VertexArray& operator=(const VertexArray& other) noexcept = delete;

        void SetVertexBuffer(const std::weak_ptr<LockableResource>& buffer) {
            mVertexBuffer = buffer;
        }

        void SetElementBuffer(const std::weak_ptr<LockableResource>& buffer) {
            mElementBuffer = buffer;
        }

        static UInt32 GetCurrent() {
            Int32 current = 0;
            glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current);
            return static_cast<UInt32>(current);
        }

        const VertexAttributeLayout& GetLayout() const {
            return mLayout;
        }

        void SetLayout(const VertexAttributeLayout& layout) {
            mLayout = layout;
            UpdateLayout();
        }

        static UInt32 GetMaxAttributes() {
            Int32 maxAttributes = 0;
            glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributes);
            return static_cast<UInt32>(maxAttributes);
        }

        void UpdateLayout() {
            if (!IsValid())
                return;
            const UInt32 lastCurrent = GetCurrent();
            Lock();
            for (int i = 0; i < GetMaxAttributes(); ++i) {
                glDisableVertexAttribArray(i);
            }

            const auto &layout = GetLayout();
            for (const auto &attribute : layout.GetAttributes()) {
                glEnableVertexAttribArray(attribute.Location);
                glVertexAttribPointer(
                    attribute.Location,
                    attribute.ElementCount,
                    attribute.ElementType,
                    attribute.Normalized,
                    layout.GetStride(),
                    reinterpret_cast<const void *>(static_cast<uintptr_t>(attribute.Offset)));
            }
            glBindVertexArray(lastCurrent);
        }

        void Lock() override {
            if (!IsValid())
                return;
            glBindVertexArray(mName);
            if (const auto buffer = mVertexBuffer.lock()) {
                buffer->Lock();
            }

            if (const auto buffer = mElementBuffer.lock()) {
                buffer->Lock();
            }
        }

        void Unlock() override {
            glBindVertexArray(0);
        }
    };
}