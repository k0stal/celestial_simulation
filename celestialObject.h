#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "point.h"

class CCelestialObject {
    public:
        CCelestialObject(void);
        CCelestialObject(CPoint centre, CPoint force, double mass);

        virtual ~CCelestialObject() = default;
        virtual void generateObjectVertices(int objectID, std::vector<int>& objectVector, std::vector<glm::vec4>& vertices) = 0;
        virtual void generateObjectIndices(int size, std::vector<GLuint>& indices) = 0;
        virtual void generateObjectUniformColors(glm::vec3& color, std::vector<GLfloat>& colors) = 0;

        glm::mat4 updatePosition(CPoint vector, const size_t timeStep );
    
    //protected:
        CPoint centre;
        CPoint force;
        double mass;
};
