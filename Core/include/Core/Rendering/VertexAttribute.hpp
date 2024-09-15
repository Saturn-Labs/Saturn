#pragma once
#include "Common/Types.hpp"

namespace Saturn {
    class VertexAttribute {
    public:
        UInt32 Location;
        UInt32 ElementCount;
        GLenum ElementType;
        GLboolean Normalized;
        UInt32 Offset;

        VertexAttribute(UInt32 location, UInt32 elementCount, GLenum elementType, GLboolean normalized, UInt32 offset) :
            Location(location),
            ElementCount(elementCount),
            ElementType(elementType),
            Normalized(normalized),
            Offset(offset) {
        }
    };
}