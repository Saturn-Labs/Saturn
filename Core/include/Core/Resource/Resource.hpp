

#pragma once

#include "Core/Exception/Exception.hpp"
#include "ResourceLocation.hpp"
#include "ResourceState.hpp"

namespace Saturn {
    /**
     * @class Resource
     * @brief Represents a resource in the Saturn framework.
     */
    class Resource {
    private:
        friend class ResourceManager;

    protected:
        ResourceManager& mManager;
        ResourceLocation mLocation;
        ResourceState mState = ResourceState::Unloaded;
        std::optional<std::exception> mException;
        
        /**
         * @brief A virtual function to load the resource.
         */
        virtual void Load() = 0;

        /**
         * @brief A virtual function to unload the resource.
         */
        virtual void Unload() = 0;

    public:
        /**
         * @brief Constructs a new Resource instance.
         * @param manager The resource manager that manages this resource.
         * @param location The location of the resource.
         */
        explicit Resource(ResourceManager& manager, const ResourceLocation& location);

        /**
         * @brief Destroys the Resource instance.
         */
        virtual ~Resource();

        /**
         * @brief Gets the location of the resource.
         * @return The location of the resource.
         */
        const ResourceLocation& GetLocation() const;

        /**
         * @brief Gets the current state of the resource.
         * @return The state of the resource.
         */
        ResourceState GetState() const;

        /**
         * @brief Gets the exception that occurred during resource loading, if any.
         * @return The exception, or an empty optional if no exception occurred.
         */
        std::optional<std::exception> GetException() const;

        /**
         * @brief Gets the ResourceManager that manages this Resource
         * @return The resource manager.
         */
        ResourceManager& GetResourceManager();

        /**
         * @brief Waits until the resource is loaded or failed, or timeout.
         * @return True if the resource was loaded succesfully, false otherwise.
         */
        bool WaitUntilLoaded(std::chrono::milliseconds timeout = 5000ms) const {
            const auto timeOutTime = timeout + std::chrono::high_resolution_clock::now();
            while (GetState() != ResourceState::Loaded && GetState() != ResourceState::Failed && timeOutTime < std::chrono::high_resolution_clock::now())
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            return GetState() == ResourceState::Loaded;
        }
    };
}