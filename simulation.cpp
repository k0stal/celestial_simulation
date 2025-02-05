#include "simulation.h"

CSimulation::CSimulation(void):
    objects(),
    view(viewMatrix),
    context(),
    window(nullptr),
    shaderProgram(),
    verticesPos(),
    colorBuffer(),
    indicesBuffer(),
    objectVector(),
    models(),
    vao(),
    ebo() {
        // window setup
        sdlSetup();
    }

void CSimulation::sdlSetup(void) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // window size definition
    this->window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    this->context = SDL_GL_CreateContext(this->window);

    glewExperimental = GL_TRUE;
    glewInit();
}

CSimulation::~CSimulation(void) {
    glDeleteProgram(this->shaderProgram);

    glDeleteBuffers(1, &this->ebo);
    glDeleteVertexArrays(1, &this->vao);

    SDL_GL_DeleteContext(this->context);
    SDL_Quit(); 
}

void CSimulation::addCelestialObject(std::shared_ptr<CCelestialObject> object) {
    objects.push_back(std::move(object));
}

void CSimulation::generateRandomObjects(const size_t count) {
    std::shared_ptr<CCelestialObject> object;
    glm::vec3 color;
    
    this->models.clear();

    // generate random objects
    for (size_t i = 0; i < count - 1; i++ ) {
        color = generateRandomColor(i);
        std::vector<double> randVec = {};
        for (size_t j = 0; j < 6; j++ ) 
            randVec.push_back(static_cast<double>((rand() % 145 - 100) / 100.0));

        if (i == 0)
            object = std::make_shared<CStar>(CPoint(0, 0, 0), CPoint(0, 0, 0), 1e7);
        else if (i % 2){
            object = std::make_shared<CPlanet>(CPoint(randVec[0], randVec[1], randVec[2]), CPoint(randVec[3], randVec[4], randVec[5]) * 1e2, 1e3);
        } else {
            object = std::make_shared<CMoon>(CPoint(randVec[0], randVec[1], randVec[2]), CPoint(randVec[3], randVec[4], randVec[5]) * 1e3, 1e1);
        }

        object->generateObjectIndices(this->verticesPos.size(), this->indicesBuffer);
        object->generateObjectUniformColors(color, this->colorBuffer);
        object->generateObjectVertices(i, this->objectVector, this->verticesPos);

        this->models.push_back(glm::translate(
            glm::mat4(1.0f), 
            glm::vec3(object->centre.posX, object->centre.posY, object->centre.posZ)
        ));

        addCelestialObject(object);
    }

    // move objects to init positions
    calcNewVerticesPos();
}

void CSimulation::runSimulation(void) {

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesBuffer.size() * sizeof(GLuint), indicesBuffer.data(), GL_STATIC_DRAW);

    createProgram();

    // // Specify the layout of the vertex data
    // GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    // glEnableVertexAttribArray(posAttrib);
    // glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    // GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    // glEnableVertexAttribArray(colAttrib);
    // glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    // GLint uniModel = glGetUniformLocation(shaderProgram, "model");

    GLint uniView = glGetUniformLocation(this->shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(this->view));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(this->shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    SDL_Event windowEvent;

    std::vector<GLfloat> verticesBuffer;
    
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) break;
        }

        /// FIX THIS
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        COctTreeNode root = COctTreeNode(CPoint(0, 0, 0), SPACE_SIZE);
        root.insert(this->objects);
        root.calculateStep(this->objects, this->models, TIME_STEP);

        if (this->models.size() == this->objects.size())
            calcNewVerticesPos();

        generateVerticesBuffer(verticesBuffer);

        /// Merge color and position buffer
        GLuint vboPos;
        glGenBuffers(1, &vboPos);
        glBindBuffer(GL_ARRAY_BUFFER, vboPos);
        glBufferData(GL_ARRAY_BUFFER, verticesBuffer.size() * sizeof(GLfloat), verticesBuffer.data(), GL_STATIC_DRAW);

        GLint posAttrib = glGetAttribLocation(this->shaderProgram, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

        GLuint vboColor;
        glGenBuffers(1, &vboColor);
        glBindBuffer(GL_ARRAY_BUFFER, vboColor);
        glBufferData(GL_ARRAY_BUFFER, this->colorBuffer.size() * sizeof(GLfloat), this->colorBuffer.data(), GL_STATIC_DRAW);

        GLint colAttrib = glGetAttribLocation(this->shaderProgram, "color");
        glEnableVertexAttribArray(colAttrib);
        glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        
        glDrawElementsInstanced(GL_TRIANGLES, this->indicesBuffer.size(), GL_UNSIGNED_INT, (void*)0, objects.size());

        glDeleteBuffers(1, &vboPos);
        glDeleteBuffers(1, &vboColor);

        SDL_GL_SwapWindow(this->window);
    }
}

void CSimulation::shaderCompilationStatus(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        throw std::runtime_error(buffer);
    }   
}

void CSimulation::createProgram(void) {
    std::string vertexCode = loadShaderSource("shaders/vertex_shader.glsl");
    std::string fragmentCode = loadShaderSource("shaders/fragment_shader.glsl");

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    shaderCompilationStatus(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    shaderCompilationStatus(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, vertexShader);
    glAttachShader(this->shaderProgram, fragmentShader);
    glBindFragDataLocation(this->shaderProgram, 0, "outColor");
    glLinkProgram(this->shaderProgram);
    glUseProgram(this->shaderProgram);

    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
}

glm::vec3 CSimulation::generateRandomColor(size_t seed) {
    // generate using HSV, keep saturation and value constant
    float h = float(seed % 10) / 10.0f; 
    float s = 1.0f;
    float v = 1.0f;

    float c = v * s;
    float x = c * (1.0f - fabsf(fmodf(h * 6.0f, 2.0f) - 1.0f));
    float m = v - c;

    glm::vec3 rgb;
    if (h < 1.0f / 6.0f) rgb = glm::vec3(c, x, 0.0f);
    else if (h < 2.0f / 6.0f) rgb = glm::vec3(x, c, 0.0f);
    else if (h < 3.0f / 6.0f) rgb = glm::vec3(0.0f, c, x);
    else if (h < 4.0f / 6.0f) rgb = glm::vec3(0.0f, x, c);
    else if (h < 5.0f / 6.0f) rgb = glm::vec3(x, 0.0f, c);
    else rgb = glm::vec3(c, 0.0f, x);

    return rgb + glm::vec3(m, m, m);
}

void CSimulation::calcNewVerticesPos(void) {
    std::vector<glm::vec4> newPos;
    for (int i = 0; i < this->verticesPos.size(); i++) {
        glm::vec4 currPos = this->verticesPos[i];
        int objectID = this->objectVector[i];
        glm::mat4 currModel = this->models[objectID];
        newPos.push_back(currModel * currPos);
    }
    this->verticesPos = newPos;
    this->models.clear();
}

void CSimulation::generateVerticesBuffer(std::vector<GLfloat>& verticesBuffer) {
    verticesBuffer.clear();
    for (const auto& pos : this->verticesPos ){
        verticesBuffer.push_back(pos[0]);
        verticesBuffer.push_back(pos[1]);
        verticesBuffer.push_back(pos[2]);
    }
}

std::string CSimulation::loadShaderSource(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}