#pragma once

#include "sphericalCelestialObject.h"

constexpr float PLANET_SIZE = 0.035f;
constexpr int PLANET_STACKS = 10;
constexpr int PLANET_SECTORS = 10;

/**
 * @class CPlanet
 * @brief Represents a planet object in the simulation.
 */
class CPlanet : public CSphericalCelestialObject {
public:
    /**
     * @brief Constructor.
     * @param centre Initial position.
     * @param force Initial force vector.
     * @param mass Mass of the planet.
     */
    CPlanet(CPoint centre, CPoint force, double mass);

    /**
     * @brief Destructor.
     */
    ~CPlanet(void) = default;

    // Future methods for planet lighting/texturing
};
