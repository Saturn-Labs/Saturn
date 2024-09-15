#pragma once
#include <glm/glm.hpp>

#include "VertexAttributeLayout.hpp"

namespace Saturn {
#pragma pack(push, 1)
    struct BasicVertex {
        glm::vec3 Position;
        glm::vec2 TexCoord;

        static VertexAttributeLayout GetLayout() {
            return VertexAttributeLayout({
                { 0, 3, GL_FLOAT, false, offsetof(BasicVertex, Position) },
                { 1, 2, GL_FLOAT, false, offsetof(BasicVertex, TexCoord) }
            });
        }
    };
#pragma pack(pop)
}