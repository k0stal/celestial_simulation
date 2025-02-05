#pragma once

#include "sphericalCelestialObject.h"

constexpr float PLANET_SIZE = 0.035f;
constexpr int PLANET_STACKS = 10;
constexpr int PLANET_SECTORS = 10;

class CPlanet : public CSphericalCelestialObject {
    public:
        CPlanet(CPoint centre, CPoint force, double mass);
        ~CPlanet(void) = default;

    // Methods for planet lighting / texturing
};