#include "Core/IO/File.hpp"

#include <filesystem>
#include <spdlog/fmt/bundled/format.h>

namespace Saturn {
    String File::ReadAllText(const String& filePath) {
        if (!fs::exists(filePath))
            throw Exception(fmt::format("File '{}' was not found!", filePath).c_str());
        const ReadFileStream rfs(filePath);
        StringStream ss;
        ss << rfs.rdbuf();
        return ss.str();
    }
}
