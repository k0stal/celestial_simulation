#include "moon.h"

CMoon::CMoon(CPoint centre, CPoint force, double mass):
    CSphericalCelestialObject(centre, force, mass, MOON_SIZE, MOON_STACKS, MOON_SECTORS) {}
