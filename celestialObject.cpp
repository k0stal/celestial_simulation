#include "celestialObject.h"

CCelestialObject::CCelestialObject( void ):
    centre(),
    force(),
    mass(0) {}

CCelestialObject::CCelestialObject( CPoint centre, CPoint force, double mass):
    centre( centre ),
    force( force ),
    mass( mass ) {}

glm::mat4 CCelestialObject::updatePosition(CPoint gravityForce, const size_t timeStep ) {
    glm::vec3 initialPos = {this->centre.posX, this->centre.posY, this->centre.posZ};

    std::cout << "Gravity: " << gravityForce << std::endl;

    // move object
    this->force = this->force + gravityForce;
    CPoint acceleration = this->force / this->mass;
    this->centre = this->centre + acceleration * timeStep * timeStep;

    glm::vec3 newPos = {this->centre.posX, this->centre.posY, this->centre.posZ};

    // calc translation matrix
    return glm::translate(glm::mat4(1.0f), newPos - initialPos);
}