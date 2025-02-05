CXX = clang++
LD = clang++
CFLAGS := -std=c++20 -Wall -pedantic -g

# SDL2 configuration
SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LDFLAGS := $(shell sdl2-config --libs)

# GLEW configuration
GLEW_CFLAGS := $(shell pkg-config --cflags glew)
GLEW_LDFLAGS := $(shell pkg-config --libs glew)

# GLM configuration
GLM_CFLAGS := $(shell pkg-config --cflags glm)
GLM_LDFLAGS := $(shell pkg-config --libs glm)

# OpenGL framework flag (Mac OS X)
OPENGL_FLAGS := -framework OpenGL

OBJS = point.o celestialObject.o sphericalCelestialObject.o planet.o star.o moon.o octTreeNode.o simulation.o test.o

all: acme_program

acme_program: $(OBJS)
	$(LD) $(CFLAGS) $(SDL2_LDFLAGS) $(GLEW_LDFLAGS) $(GLM_LDFLAGS) $(OPENGL_FLAGS) -o $@ $^

clear:
	rm -f acme_program $(OBJS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(SDL2_CFLAGS) $(GLM_CFLAGS) $(GLEW_CFLAGS) -c $<
