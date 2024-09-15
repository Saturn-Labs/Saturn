#include "pch.hpp"
#include "Core/Resource/ResourceLocation.hpp"
#include "Core/IO/File.hpp"

namespace Saturn {
    ResourceLocation::ResourceLocation() {}

    ResourceLocation::ResourceLocation(const std::string& path) {
        mPaths["resource"] = path;
    }

    ResourceLocation::ResourceLocation(const std::map<std::string, std::string>& paths) :
        mPaths(paths) {
    }

    bool ResourceLocation::IsMultipleLocation() const {
        return mPaths.size() > 1;
    }

    bool ResourceLocation::HasResourcePath() const {
        return mPaths.contains("resource");
    }

    std::string ResourceLocation::GetResourcePath() const {
        if (!mPaths.contains("resource"))
            throw std::exception(std::format("ResourceLocation doesn't contain key '{}'!", "resource").c_str());
        return mPaths.at("resource");
    }

    void ResourceLocation::AddPath(const std::string& key, const std::string& value) {
        mPaths[key] = value;
    }

    void ResourceLocation::RemovePath(const std::string& key) {
        mPaths.erase(key);
    }

    std::string ResourceLocation::GetPath(const std::string& key) const {
        if (!mPaths.contains(key))
            throw std::exception(std::format("ResourceLocation doesn't contain key '{}'!", key).c_str());
        return mPaths.at(key);
    }

    bool ResourceLocation::HasPath(const std::string& key) const {
        return mPaths.contains(key);
    }

    std::size_t ResourceLocation::GetHashCode() const {
        std::size_t seed = 0;
        for (const auto& [key, path] : mPaths) {
            std::hash<std::string> hasher;
            seed += hasher(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed += hasher(path) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }

    std::string ResourceLocation::GetIdentifier() const {
        return std::format("ResourceLocation[{:x}]", GetHashCode());
    }

    bool ResourceLocation::FilesExist() const {
        return std::ranges::all_of(mPaths, [](const std::pair<const std::string, std::string>& elements) {
            return File::Exists(elements.second);
        });
    }
}
