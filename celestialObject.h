#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "point.h"

/**
 * @class CCelestialObject
 * @brief Abstract base class representing a celestial object.
 */
class CCelestialObject {
public:
    /**
     * @brief Default constructor.
     */
    CCelestialObject(void);

    /**
     * @brief Constructor with parameters.
     * @param centre Initial position of the object.
     * @param force Initial force vector acting on the object.
     * @param mass Mass of the object.
     */
    CCelestialObject(CPoint centre, CPoint force, double mass);

    /**
     * @brief Virtual destructor.
     */
    virtual ~CCelestialObject() = default;

    /**
     * @brief Pure virtual method to generate object vertices.
     * @param objectID ID of the object.
     * @param objectVector Vector to store object indices.
     * @param vertices Vector to store vertex positions.
     */
    virtual void generateObjectVertices(int objectID, std::vector<int>& objectVector, std::vector<glm::vec4>& vertices) = 0;

    /**
     * @brief Pure virtual method to generate index buffer for the object.
     * @param size Size of the object data.
     * @param indices Vector to store index data.
     */
    virtual void generateObjectIndices(int size, std::vector<GLuint>& indices) = 0;

    /**
     * @brief Pure virtual method to generate uniform color values for the object.
     * @param color RGB color.
     * @param colors Output vector of colors.
     */
    virtual void generateObjectUniformColors(glm::vec3& color, std::vector<GLfloat>& colors) = 0;

    /**
     * @brief Updates the position of the object.
     * @param vector Velocity vector or force influence.
     * @param timeStep Time step for the simulation.
     * @return Updated transformation matrix.
     */
    glm::mat4 updatePosition(CPoint vector, const size_t timeStep);

    CPoint centre;
    CPoint force;
    double mass;
};
