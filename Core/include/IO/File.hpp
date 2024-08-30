#pragma once
#include <filesystem>
#include "Common/Types.hpp"
#include "Stream/Buffer.hpp"

namespace fs = std::filesystem;
namespace Saturn {
    enum class OpenMode {
        Read = 1,
        Write = 2,
        ReadWrite = Read | Write
    };

    class File {
    public:
        static FileStream Open(const fs::path& path, OpenMode mode = OpenMode::ReadWrite);
        static String ReadAllText(const fs::path& path);
        static Buffer ReadAllBytes(const fs::path& path);
        static bool Exists(const fs::path& path);
    };
}