#include <iostream>

#include "./Matrix/ATSPMatrix.h"
#include "./Solutions/Utils/GreedyAlgorithm.h"
#include "./Solutions/SimulatedAnnealing.h"

int main() {
    ATSPMatrix *matrix = new ATSPMatrix();
    matrix->loadFromFile("../Resources/br17");
    

    system("PAUSE");
    return 0;
}
