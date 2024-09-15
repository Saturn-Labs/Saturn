#pragma once
#include <glad/gl.h>

#include "BufferUsagePattern.hpp"
#include "Common/Types.hpp"
#include "Core/Rendering/LockableResource.hpp"

namespace Saturn {
    template<typename TElement>
    class ElementBuffer final : public LockableResource<UInt32, 0> {
        std::vector<TElement> mElements;
    public:
        explicit ElementBuffer(const std::vector<TElement>& elements, BufferUsageHint usageHint = BufferUsageHint::StaticDraw) :
            mElements(elements) {
            SetElements(elements, usageHint);
        }

        ~ElementBuffer() noexcept override {
            if (!ElementBuffer::IsValid())
                return;
            glDeleteBuffers(1, &mName);
        }

        ElementBuffer(ElementBuffer&& other) noexcept = delete;
        ElementBuffer& operator=(ElementBuffer&& other) noexcept = delete;
        ElementBuffer(const ElementBuffer& other) = delete;
        ElementBuffer& operator=(const ElementBuffer& other) noexcept = delete;

        void SetElements(const std::vector<TElement>& elements, BufferUsageHint usageHint = BufferUsageHint::StaticDraw) {
            if (!IsValid()) {
                glGenBuffers(1, &mName);
            }
            const UInt32 lastCurrent = GetCurrent();
            Lock();
            mElements = elements;
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(TElement) * mElements.size(), mElements.data(), static_cast<GLenum>(usageHint));
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lastCurrent);
        }

        static UInt32 GetCurrent() {
            Int32 current = 0;
            glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &current);
            return static_cast<UInt32>(current);
        }

        UInt32 GetElementCount() const {
            return mElements.size();
        }

        static std::shared_ptr<ElementBuffer> Create(const std::vector<TElement> &elements, BufferUsageHint usageHint = BufferUsageHint::StaticDraw) {
            return std::make_shared<ElementBuffer>(elements, usageHint);
        }

        void Lock() override {
            if (!IsValid())
                return;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mName);
        }

        void Unlock() override {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    };
}