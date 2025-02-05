#include "simulation.h"

constexpr size_t SIM_OBJ_NR = 100;

int main(int argc, char *argv[]) {
    CSimulation simulation;
    simulation.generateRandomObjects(SIM_OBJ_NR);
    simulation.runSimulation();

    return 0;
}
