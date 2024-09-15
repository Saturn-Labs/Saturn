/**
 * @file ResourceUnloader.hpp
 * @brief Contains the declaration of the ResourceUnloader class.
 * @namespace Saturn
 */

#pragma once

namespace Saturn {
    class Resource;
    class ResourceManager;

    /**
     * @class ResourceUnloader
     * @brief A class that provides a mechanism to unload resources from a resource manager.
     * This class is designed to be used as a function object with the ResourceManager.
     */
    class ResourceUnloader {
    private:
        friend class ResourceManager;

        /**
         * @brief A reference to the resource manager that will be used to unload resources.
         */
        ResourceManager& mManager;

    public:
        /**
         * @brief Constructor for the ResourceUnloader class.
         *
         * @param[in] manager - The resource manager that will be used to unload resources.
         */
        explicit ResourceUnloader(ResourceManager& manager) : mManager(manager) {}

        /**
         * @brief Function that unloads a resource from the resource manager.
         *
         * @param[in] resource - The resource to be unloaded.
         * @return void
         */
        void operator()(Resource* resource) const;
    };
}