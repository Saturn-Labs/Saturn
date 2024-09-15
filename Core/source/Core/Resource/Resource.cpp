#include "pch.hpp"
#include "Core/Resource/Resource.hpp"

namespace Saturn {
    class Exception;

    Resource::Resource(ResourceManager& manager, const ResourceLocation& location) :
        mManager(manager),
        mLocation(location) {
    }

    Resource::~Resource() = default;

    const ResourceLocation& Resource::GetLocation() const {
        return mLocation;
    }

    ResourceState Resource::GetState() const {
        return mState;
    }

    std::optional<std::exception> Resource::GetException() const {
        return mException;
    }

    ResourceManager& Resource::GetResourceManager() {
        return mManager;
    }
}
