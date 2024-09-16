#pragma once
#include "Resource.hpp"
#include "ResourceUnloader.hpp"
#include "Common/Types.hpp"
#include "Core/Context.hpp"

namespace Saturn {
    class Application;

    /**
     * @class ResourceManager
     * @brief This class contains functions for loading and unloading resources asyncronously.
     *
     * Example:
     * @code
     * ResourceManager& resources = ...;
     * ResourceLocation location("assets/myresource.res");
     * std::shared_ptr<MyResource> resource = resources.LoadResource<MyResource>(location);
     * ...check if resource has been loaded...
     * @endcode
     */
    class ResourceManager {
        using ResourceMap = std::unordered_map<std::string, std::weak_ptr<Resource>>;
        friend class Framework;
        friend class ResourceUnloader;

        ResourceMap mResources = {};
        std::shared_ptr<Context> mManagerContext;

        /**
         * @brief Unloads a resource from the resources cache.
         *
         * This function removes a resource from the cache. It is intended for internal use only
         * and should only be called by the `ResourceUnloader` class within a `std::shared_ptr` context.
         *
         * @param[in] iterator An iterator to the resource in the `ResourceMap` that needs to be unloaded.
         * @see ResourceUnloader
         */
        void UnloadResourceAt(const ResourceMap::iterator& iterator) {
            if (iterator == mResources.end())
                return;
            mResources.erase(iterator);
        }
        
        ResourceManager();
        ~ResourceManager();
    public:

        /**
         * @template T
         * @brief Asynchronously loads a resource of type T from the specified location.
         *
         * If the resource is already loaded, the existing resource is returned. Otherwise, a new resource
         * is created, loaded asynchronously, and returned.
         *
         * @param[in] location The location of the resource to load.
         * @return A shared pointer to the loaded resource.
         */
        template <typename T, typename... TArgs>
        std::shared_ptr<T> LoadResource(const ResourceLocation& location, TArgs&&... args) {
            if (mResources.contains(location.GetIdentifier()))
                return std::static_pointer_cast<T>(mResources[location.GetIdentifier()].lock());

            // Create and load the resource asynchronously
            std::shared_ptr<T> resourcePtr = std::shared_ptr<T>(new T(*this, location, std::forward<TArgs>(args)...), ResourceUnloader(*this));
            mResources[location.GetIdentifier()] = resourcePtr;
            auto future = std::async(std::launch::async, [*this, resourcePtr] {
                GetContext().SetThisAsCurrentContext();
                Resource& resource = *resourcePtr;
                resource.mState = ResourceState::Loading;
                try {
                    resource.Load();
                    resource.mState = ResourceState::Loaded;
                    resource.mException = std::nullopt;
                }
                catch (const std::exception& e) {
                    resource.mState = ResourceState::Failed;
                    resource.mException = e;
                }
            });
            return resourcePtr;
        }

        template<typename Lambda>
        void WorkInResourceContextAsync(Lambda func, bool wait = false) {
            auto future = std::async(std::launch::async, [*this, &func] {
                GetContext().SetThisAsCurrentContext();
                func();
            });
            if (wait)
                future.get();
        }

        Context& GetContext() const;
    };
}
