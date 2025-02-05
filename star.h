#pragma once

#include "sphericalCelestialObject.h"

constexpr float STAR_SIZE = 0.09f;
constexpr int STAR_STACKS = 15;
constexpr int STAR_SECTORS = 15;

class CStar : public CSphericalCelestialObject {
    public:
        CStar(CPoint centre, CPoint force, double mass);
        ~CStar(void) = default;

    // Methods for star lighting / texturing
};