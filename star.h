#pragma once

#include "sphericalCelestialObject.h"

constexpr float STAR_SIZE = 0.09f;
constexpr int STAR_STACKS = 15;
constexpr int STAR_SECTORS = 15;

/**
 * @class CStar
 * @brief Represents a star object in the simulation, inheriting spherical geometry and behavior.
 * 
 * Inherits from CSphericalCelestialObject and may support star-specific lighting or texturing logic.
 */
class CStar : public CSphericalCelestialObject {
public:
    /**
     * @brief Constructs a CStar object.
     * @param centre Initial position of the star.
     * @param force Initial force acting on the star.
     * @param mass Mass of the star.
     */
    CStar(CPoint centre, CPoint force, double mass);

    /**
     * @brief Destructor.
     */
    ~CStar(void) = default;

    // Future methods for star-specific rendering (e.g. glow, texture, dynamic light) can be added here
};
