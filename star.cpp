#include "star.h"

CStar::CStar(CPoint centre, CPoint force, double mass):
    CSphericalCelestialObject(centre, force, mass, STAR_SIZE, STAR_STACKS, STAR_SECTORS) {}