#include "../include/Log.h"
#include "../include/Simulation.h"

int main() {
    Log::init();
    Simulation::getInstance()->run();
    return 0;
}