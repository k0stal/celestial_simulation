#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "celestialObject.h"
#include "moon.h"
#include "planet.h"
#include "star.h"
#include "octTreeNode.h"

#include <vector>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// move to config?
constexpr size_t SPACE_SIZE = 2;
constexpr size_t TIME_STEP = 1;

const glm::mat4 viewMatrix = glm::lookAt(
    glm::vec3(3.0f, 3.0f, 3.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f)
);

class CSimulation {
    public:
        CSimulation(void);
        ~CSimulation();
        void addCelestialObject(std::shared_ptr<CCelestialObject> object);
        void generateRandomObjects(const size_t count);
        void runSimulation(void);

    private:
        void sdlSetup(void);
        std::string loadShaderSource(const std::string& filePath);
        void shaderCompilationStatus(GLuint shader);
        void initAndBindEBO(void);

        // Merge color and position buffer
        void initVBO(void);
        void createProgram(void);

        glm::vec3 generateRandomColor(size_t seed);
        void generateVerticesBuffer(std::vector<GLfloat>& verticesBuffer);

        void calcNewVerticesPos(void);

        std::vector<std::shared_ptr<CCelestialObject>> objects;
        glm::mat4 view;

        SDL_GLContext context;
        SDL_Window* window;

        GLuint shaderProgram;

        std::vector<glm::vec4> verticesPos;
        std::vector<GLfloat> colorBuffer;
        std::vector<GLuint> indicesBuffer;
        std::vector<int> objectVector;
        std::vector<glm::mat4> models;

        GLuint vao;
        GLuint ebo;
};