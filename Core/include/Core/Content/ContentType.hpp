#pragma once

namespace Saturn {
    enum class ContentType {
        UnknownContent = -1,
        ShaderContent
    };
}

#define CONTENT_TYPE(x) \
    static Saturn::ContentType GetContentType() { return Saturn::ContentType::x; }