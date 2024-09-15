#include "pch.hpp"
#include "Core/Rendering/VertexAttributeLayout.hpp"

#include "Core/Logger.hpp"
#include "Core/Rendering/Utils/GLTypeHelper.hpp"

namespace Saturn {
    VertexAttributeLayout::VertexAttributeLayout() = default;
    VertexAttributeLayout::VertexAttributeLayout(const std::vector<VertexAttribute> &attributes) :
        mAttributes(attributes) {
        RecalculateStride();
    }

    VertexAttributeLayout::~VertexAttributeLayout() = default;

    UInt32 VertexAttributeLayout::GetStride() const {
        return mStride;
    }

    void VertexAttributeLayout::SetStride(UInt32 stride) {
        mStride = stride;
    }

    const std::vector<VertexAttribute> &VertexAttributeLayout::GetAttributes() const {
        return mAttributes;
    }

    std::vector<VertexAttribute> &VertexAttributeLayout::GetAttributes() {
        return mAttributes;
    }

    void VertexAttributeLayout::SetAttributes(const std::vector<VertexAttribute> &attributes) {
        mAttributes = attributes;
        RecalculateStride();
    }

    void VertexAttributeLayout::RecalculateStride() {
        mStride = 0;
        for (const auto& attribute : mAttributes) {
            const auto size = GLTypeHelper::GetGLtypeSize(attribute.ElementType);
            mStride += size * attribute.ElementCount;
        }
    }

    void VertexAttributeLayout::AddAttribute(const VertexAttribute &attribute) {
        mAttributes.push_back(attribute);
        RecalculateStride();
    }

    void VertexAttributeLayout::RemoveAttribute(UInt32 location) {
        const auto it = std::ranges::find_if(
            mAttributes, [location](const VertexAttribute &attr) { return attr.Location == location; });

        if (it != mAttributes.end()) {
            mAttributes.erase(it);
            RecalculateStride();
        }
    }

    void VertexAttributeLayout::ClearAttributes() {
        mAttributes.clear();
        mStride = 0;
    }

    std::string VertexAttributeLayout::ToString() const {
        std::string str = "VertexAttributeLayout:\n";
        if (mAttributes.empty())
            str += " - No attributes...";
        for (const auto& attribute : mAttributes) {
            str += std::format(" - [\"Location\":{}, \"ElementCount\":{}, \"ElementType\":\"{}\", \"Normalized\":{}, \"Offset\":{}]\n",
                attribute.Location, attribute.ElementCount, GLTypeHelper::GetCppTypeForGLenum(attribute.ElementType).name(), attribute.Normalized ? true : false, attribute.Offset);
        }
        str += " - Stride: " + std::to_string(mStride) + "\n";
        return str;
    }

    void VertexAttributeLayout::Print() const {
        std::istringstream stream(ToString());
        std::string line;
        while (std::getline(stream, line)) {
            Logger::Trace("{}", line);
        }
    }
}
