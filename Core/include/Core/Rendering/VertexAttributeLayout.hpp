#pragma once
#include "VertexAttribute.hpp"

namespace Saturn {
    class VertexAttributeLayout {
        std::vector<VertexAttribute> mAttributes = {};
        UInt32 mStride = 0;
    public:
        explicit VertexAttributeLayout();
        explicit VertexAttributeLayout(const std::vector<VertexAttribute>& attributes);
        ~VertexAttributeLayout();

        UInt32 GetStride() const;
        void SetStride(UInt32 stride);
        const std::vector<VertexAttribute>& GetAttributes() const;
        std::vector<VertexAttribute>& GetAttributes();
        void SetAttributes(const std::vector<VertexAttribute>& attributes);
        void RecalculateStride();
        void AddAttribute(const VertexAttribute& attribute);
        void RemoveAttribute(UInt32 location);
        void ClearAttributes();
        std::string ToString() const;
        void Print() const;
    };
}