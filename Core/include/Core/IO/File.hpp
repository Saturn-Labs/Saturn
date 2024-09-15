#pragma once
#include "Common/Types.hpp"

namespace fs = std::filesystem;
namespace Saturn {
    class File {
    public:
        static std::string ReadAllText(const std::string& filePath);
        static bool Exists(const std::string& filePath);
    };
}
