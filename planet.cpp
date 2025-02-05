#include "planet.h"

CPlanet::CPlanet(CPoint centre, CPoint force, double mass):
    CSphericalCelestialObject(centre, force, mass, PLANET_SIZE, PLANET_STACKS, PLANET_SECTORS) {}
