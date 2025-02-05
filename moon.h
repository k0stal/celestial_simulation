#pragma once

#include "sphericalCelestialObject.h"

constexpr float MOON_SIZE = 0.01f;
constexpr int MOON_STACKS = 5;
constexpr int MOON_SECTORS = 5;

class CMoon : public CSphericalCelestialObject {
    public:
        CMoon(CPoint centre, CPoint force, double mass);
        ~CMoon(void) = default;

    // Methods for planet lighting / texturing
};