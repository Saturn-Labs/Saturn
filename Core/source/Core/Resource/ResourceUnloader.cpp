#include "pch.hpp"
#include "Saturn.hpp"
#include "Core/Resource/ResourceUnloader.hpp"
#include "Core/Resource/ResourceManager.hpp"
#include "Core/Application.hpp"
#include "Core/Logger.hpp"

namespace Saturn {
    void ResourceUnloader::operator()(Resource* resource) const {
        if (!resource)
            return;
        auto future = std::async(std::launch::async, [resource] {
            ResourceManager& manager = resource->GetResourceManager();
            manager.GetContext().SetThisAsCurrentContext();
            const auto resourceIterator = manager.mResources.find(resource->GetLocation().GetIdentifier());
            manager.UnloadResourceAt(resourceIterator);
            Logger::Debug("Unloaded resource: {}", resource->GetLocation().GetIdentifier());
            delete resource;
        });
        future.get();
    }
}
