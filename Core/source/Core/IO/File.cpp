#include "pch.hpp"
#include "Core/IO/File.hpp"

namespace Saturn {
    std::string File::ReadAllText(const std::string& filePath) {
        if (!fs::exists(filePath))
            throw std::exception(fmt::format("File '{}' was not found!", filePath).c_str());
        const std::ifstream rfs(filePath);
        std::stringstream ss;
        ss << rfs.rdbuf();
        return ss.str();
    }

    bool File::Exists(const std::string& filePath) {
        return fs::exists(filePath);
    }
}
