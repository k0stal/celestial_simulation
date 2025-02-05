#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

#include "celestialObject.h"

const float PI = 3.14159265359f;

class CSphericalCelestialObject : public CCelestialObject {
    public:
        CSphericalCelestialObject(CPoint centre, CPoint force, double mass, float radius, int stacks, int sectors);
        ~CSphericalCelestialObject() = default;

        void generateObjectVertices(int objectID, std::vector<int>& objectVector, std::vector<glm::vec4>& vertices) override;
        void generateObjectIndices(int size, std::vector<GLuint>& indices) override;
        void generateObjectUniformColors(glm::vec3& color, std::vector<GLfloat>& colors) override;

    protected:
        float radius;
        int stacks;
        int sectors;
};