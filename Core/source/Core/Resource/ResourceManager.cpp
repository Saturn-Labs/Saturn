#include "pch.hpp"
#include "Core/Resource/ResourceManager.hpp"

namespace Saturn {
    ResourceManager::ResourceManager() :
        mManagerContext(Context::Create({ true, { "ResourceManagerContext" } })) {
    }

    ResourceManager::~ResourceManager() {
    }

    Context& ResourceManager::GetContext() const {
        return *mManagerContext;
    }
}
