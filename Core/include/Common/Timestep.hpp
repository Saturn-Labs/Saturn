/**
 * @brief Represents a time step in a game loop.
 *
 * @class Timestep
 * @namespace Saturn
 */
#pragma once

namespace Saturn {
    /**
     * @brief A class representing a time step in a game loop.
     */
    class Timestep {
    public:
        /**
         * @brief The duration of the time step in seconds.
         */
        double Delta = 0;

        /**
         * @brief Constructor for Timestep.
         *
         * @param deltaTime The duration of the time step in seconds.
         */
        explicit Timestep(double deltaTime) :
            Delta(deltaTime) {
        }
    };
}