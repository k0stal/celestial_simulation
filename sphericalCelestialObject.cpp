#include "sphericalCelestialObject.h"

CSphericalCelestialObject::CSphericalCelestialObject(CPoint centre, CPoint force, double mass, float radius, int stacks, int sectors):
    CCelestialObject(centre, force, mass),
    radius(radius),
    stacks(stacks),
    sectors(sectors) {}

void CSphericalCelestialObject::generateObjectVertices(int objectID, std::vector<int>& objectVector, std::vector<glm::vec4>& vertices) {
    float sectorStep = 2 * PI / this->sectors;
    float stackStep = PI / this->stacks;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= this->stacks; ++i) {
        stackAngle = PI / 2 - i * stackStep;
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);

        for (int j = 0; j <= this->sectors; ++j) {
            sectorAngle = j * sectorStep;

            // Vertex positions
            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            // Store vertex position
            vertices.push_back(glm::vec4(x, y, z, 1.0));
            objectVector.push_back(objectID);
        }
    }
}

void CSphericalCelestialObject::generateObjectIndices(int size, std::vector<GLuint>& indices) {
    for (int i = 0; i < this->stacks; ++i) {
        int k1 = i * (this->sectors + 1);
        int k2 = k1 + this->sectors + 1;

        for (int j = 0; j < this->sectors; ++j, ++k1, ++k2) {
            // First triangle
            if (i != 0) {
                indices.push_back(k1 + size);
                indices.push_back(k2 + size);
                indices.push_back(k1 + 1 + size);
            }

            // Second triangle
            if (i != (this->stacks - 1)) {
                indices.push_back(k1 + 1 + size);
                indices.push_back(k2 + size);
                indices.push_back(k2 + 1 + size);
            }
        }
    }
}

void CSphericalCelestialObject::generateObjectUniformColors(glm::vec3& color, std::vector<GLfloat>& colors) {
    for (int i = 0; i <= this->stacks; ++i) {
        for (int j = 0; j <= this->sectors; ++j) {
            colors.push_back(color[0]);
            colors.push_back(color[1]);
            colors.push_back(color[2]);
        }
    }
}