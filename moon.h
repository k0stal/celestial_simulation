#pragma once

#include "sphericalCelestialObject.h"

constexpr float MOON_SIZE = 0.01f;
constexpr int MOON_STACKS = 5;
constexpr int MOON_SECTORS = 5;

/**
 * @class CMoon
 * @brief Represents a moon, derived from CSphericalCelestialObject.
 */
class CMoon : public CSphericalCelestialObject {
public:
    /**
     * @brief Constructor.
     * @param centre Initial position.
     * @param force Initial force vector.
     * @param mass Mass of the moon.
     */
    CMoon(CPoint centre, CPoint force, double mass);

    /**
     * @brief Destructor.
     */
    ~CMoon(void) = default;

    // Future methods for moon lighting/texturing
};
