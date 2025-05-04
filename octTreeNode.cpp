#include "octTreeNode.h"
        
COctTreeNode::COctTreeNode(CPoint centre, double length):
    simulationCentre(centre),
    centreOfMass(),
    totalMass( 0 ),
    length( length ),
    object( nullptr ) {
    for ( size_t i = 0; i < 8; i++ )
        children[i] = nullptr;
}

COctTreeNode::~COctTreeNode() {
    for (size_t i = 0; i < 8; i++ )
        delete children[i];
}

void COctTreeNode::insert(std::vector<std::shared_ptr<CCelestialObject>>& objects) {
    for (auto& child : objects)
        insertObject(child);
}

void COctTreeNode::insertObject(std::shared_ptr<CCelestialObject> object){
    if ( this->object == nullptr ) {
        this->object = object;
        this->centreOfMass = object->centre;
        this->totalMass = object->mass;
        return;
    }

    this->centreOfMass = ((this->centreOfMass * this->totalMass + object->centre * object->mass) /
                          (totalMass + object->mass));
    this->totalMass += object->mass;

    if ( this->children[0] == nullptr )
        splitNode();
    
    for ( auto & child : children )
        if (child->contains(object->centre)) {
            child->insertObject(object);
            break;
        }
}

void COctTreeNode::splitNode(void) {
    double newLength = length / 2;
    double quaterLength = newLength / 2;
    CPoint newCenter;
    newCenter = newCenter - CPoint( quaterLength, quaterLength, quaterLength);
    for (size_t i = 0; i < 8; i++) {
        if ((i % 4) == 1)
            newCenter.posX = newCenter.posX + newLength;
        if ((i % 4) == 2)
            newCenter.posY = newCenter.posY + newLength;
        if ((i % 4) == 3)
            newCenter.posX = newCenter.posX - newLength;
        if (i == 4) {
            newCenter.posZ = newCenter.posZ + newLength;
            newCenter.posY = newCenter.posY - newLength;
        }
        
        children[i] = new COctTreeNode(newCenter, newLength);
    }
}

bool COctTreeNode::contains(const CPoint& point) const {
    return fabs(point.posX - this->simulationCentre.posX) <= this->length / 2 &&
           fabs(point.posY - this->simulationCentre.posY) <= this->length / 2 &&
           fabs(point.posZ - this->simulationCentre.posZ) <= this->length / 2;
}

void COctTreeNode::calculateStep(std::vector<std::shared_ptr<CCelestialObject>>& objects, std::vector<glm::mat4>& transformationMatrices, const size_t timeStep ) {
    for (size_t i = 0; i < objects.size(); i++ ) {
        glm::mat4 translationMatrix = objects[i]->updatePosition(calculateForce(objects[i]), timeStep);
        if ( transformationMatrices.size() != objects.size() )
            transformationMatrices.push_back(translationMatrix);
        else {
            glm::mat4 baseMatrix = transformationMatrices[i];
            baseMatrix = translationMatrix * baseMatrix;
            transformationMatrices[i] = baseMatrix;
        }
    }
}

// Refract
CPoint COctTreeNode::calculateForce(std::shared_ptr<CCelestialObject> object) {
    CPoint force;
    if ( this->totalMass == 0 )
        return force;

    if ( this->object == object ) {
        for (const auto& child : this->children)
            if (child != nullptr)
                force = force + child->calculateForce(object); 
        return force; 
    }

    double distance = object->centre.distance(this->centreOfMass);
    if ( this->length / distance < THETA || this->children[0] == nullptr) {
        CPoint direction = this->centreOfMass - object->centre;
        double magnitude = G * object->mass * this->totalMass / (distance * distance);
        force = direction * (magnitude / distance);
    } else {
        distance = object->centre.distance(this->object->centre);
        CPoint direction = this->object->centre - object->centre;
        double magnitude = G * object->mass * this->object->mass / (distance * distance);
        force = direction * (magnitude / distance);
        for (const auto& child : this->children)
            if (child != nullptr)
                force = force + child->calculateForce(object);
    }

    return force;
}