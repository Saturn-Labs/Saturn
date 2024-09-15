#pragma once

namespace Saturn {
    /**
     * @brief Enum representing the loading state of a resource.
     *
     * This enum tracks the state of a resource during its lifecycle, from being
     * uninitialized to being loaded or failed.
     */
    enum class ResourceState {
        /**
         * @brief The resource has not been loaded.
         */
        Unloaded,  /**< The resource hasn't been loaded yet. */

        /**
         * @brief The resource is currently being loaded.
         */
        Loading,        /**< The resource is in the process of being loaded. */

        /**
         * @brief The resource has been successfully loaded.
         */
        Loaded,         /**< The resource has been loaded successfully. */

        /**
         * @brief The resource failed to load.
         */
        Failed          /**< Loading the resource failed. */
    };
}