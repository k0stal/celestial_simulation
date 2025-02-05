#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <vector>
#include <memory>

#include "point.h"
#include "celestialObject.h"

const double THETA = 0.5;
const double G = 6.6743e-10;

class COctTreeNode {
    public:
        COctTreeNode(CPoint centre, double length);
        ~COctTreeNode();
        void insert(std::vector<std::shared_ptr<CCelestialObject>>& objects);
        void calculateStep(std::vector<std::shared_ptr<CCelestialObject>>& objects, std::vector<glm::mat4>& transformationMatrices, const size_t timeStep);

    private:
        void insertObject(std::shared_ptr<CCelestialObject> object);
        void splitNode(void);
        bool contains(const CPoint& point) const;
        CPoint calculateForce(std::shared_ptr<CCelestialObject> point);

        CPoint simulationCentre;
        CPoint centreOfMass;
        double totalMass;
        double length;
        std::shared_ptr<CCelestialObject> object;
        COctTreeNode* children[8];
};