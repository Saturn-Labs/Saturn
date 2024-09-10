#pragma once
#include "Common/Types.hpp"

namespace fs = std::filesystem;
namespace Saturn {
    class File {
    public:
        static String ReadAllText(const String& filePath);
    };
}
