#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "celestialObject.h"

const float PI = 3.14159265359f;

/**
 * @class CSphericalCelestialObject
 * @brief Abstract class representing a spherical celestial object such as a planet, moon, or star.
 * 
 * Provides functionality to generate geometry (vertices, indices) and colors for a sphere-like object.
 */
class CSphericalCelestialObject : public CCelestialObject {
public:
    /**
     * @brief Constructor for a spherical celestial object.
     * @param centre Initial position of the object.
     * @param force Initial force vector acting on the object.
     * @param mass Mass of the object.
     * @param radius Radius of the spherical shape.
     * @param stacks Number of vertical segments used in rendering the sphere.
     * @param sectors Number of horizontal segments used in rendering the sphere.
     */
    CSphericalCelestialObject(CPoint centre, CPoint force, double mass, float radius, int stacks, int sectors);

    /**
     * @brief Destructor.
     */
    ~CSphericalCelestialObject() = default;

    /**
     * @brief Generates the vertices for the spherical object.
     * @param objectID ID of the object.
     * @param objectVector Vector storing the object IDs for reference.
     * @param vertices Output vector of vertex positions.
     */
    void generateObjectVertices(int objectID, std::vector<int>& objectVector, std::vector<glm::vec4>& vertices) override;

    /**
     * @brief Generates the index buffer for rendering the sphere.
     * @param size Size of the vertex buffer.
     * @param indices Output vector of index data.
     */
    void generateObjectIndices(int size, std::vector<GLuint>& indices) override;

    /**
     * @brief Generates uniform color data for the object.
     * @param color The color to assign to all vertices.
     * @param colors Output vector of color values.
     */
    void generateObjectUniformColors(glm::vec3& color, std::vector<GLfloat>& colors) override;

protected:
    float radius;
    int stacks;
    int sectors;
};
