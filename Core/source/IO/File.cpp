#include "IO/File.hpp"
#include <Common/Types.hpp>
#include <spdlog/fmt/bundled/format.h>

namespace Saturn {
    FileStream File::Open(const fs::path &path, OpenMode mode) {
        FileStream stream(path, std::ios::binary | static_cast<const int>(mode));
        if (!stream.is_open())
            throw std::exception(fmt::format("Failed to open file: {}", path.string()).c_str());
        return stream;
    }

    std::string File::ReadAllText(const fs::path &path) {
        const ReadFileStream stream(path, std::ios::binary | std::ios::in);
        std::stringstream buffer;
        buffer << stream.rdbuf();
        return buffer.str();
    }

    Buffer File::ReadAllBytes(const fs::path &path) {
        ReadFileStream stream(path, std::ios::binary | std::ios::in);
        const UInt64 size = fs::file_size(path);
        Buffer buffer(size);
        stream.read(static_cast<char*>(buffer.GetData()), size);
        return buffer;
    }

    bool File::Exists(const fs::path &path) {
        return fs::exists(path);
    }
}
