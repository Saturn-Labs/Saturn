/**
 * @file ResourceLocation.hpp
 * @brief Contains the declaration of the ResourceLocation class.
 * @namespace Saturn
 */

#pragma once
#include "Common/Types.hpp"

namespace Saturn {
    /**
     * @class ResourceLocation
     * @brief Represents a location for resources in the Saturn namespace.
     */
    class ResourceLocation {
        std::map<std::string, std::string> mPaths;

    public:
        /**
         * @brief Constructs an empty ResourceLocation.
         */
        explicit ResourceLocation();

        /**
         * @brief Constructs a ResourceLocation with a single path.
         * @param path The path to the resource.
         */
        ResourceLocation(const std::string& path);

        /**
         * @brief Constructs a ResourceLocation with multiple paths.
         * @param paths The paths to the resources.
         */
        explicit ResourceLocation(const std::map<std::string, std::string>& paths);

        /**
         * @brief Checks if the ResourceLocation has multiple paths.
         * @return True if the ResourceLocation has multiple paths, false otherwise.
         */
        bool IsMultipleLocation() const;

        /**
         * @brief Checks if the ResourceLocation has a resource path.
         * @return True if the ResourceLocation has a resource path, false otherwise.
         */
        bool HasResourcePath() const;

        /**
         * @brief Gets the resource path from the ResourceLocation.
         * @return The resource path.
         */
        std::string GetResourcePath() const;

        /**
         * @brief Adds a path to the ResourceLocation.
         * @param key The key for the path.
         * @param value The path value.
         */
        void AddPath(const std::string& key, const std::string& value);

        /**
         * @brief Removes a path from the ResourceLocation.
         * @param key The key for the path to remove.
         */
        void RemovePath(const std::string& key);

        /**
         * @brief Gets a path from the ResourceLocation.
         * @param key The key for the path.
         * @return The path value.
         */
        std::string GetPath(const std::string& key) const;

        /**
         * @brief Checks if the ResourceLocation has a specified key-path.
         * @return True if it contains the path, otherwise false.
         */
        bool HasPath(const std::string& key) const;

        /**
         * @brief Gets a hash code for the ResourceLocation.
         * @return The hash code.
         */
        std::size_t GetHashCode() const;

        /**
         * @brief Gets an identifier for the ResourceLocation.
         * @return The identifier in 'ResourceLocation[...paths hash code...]' format.
         */
        std::string GetIdentifier() const;

        /**
         * @brief Checks if the files associated with the ResourceLocation exist.
         * @return True if the files exist, false otherwise.
         */
        bool FilesExist() const;
    };
}