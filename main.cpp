#include <iostream>
#include <random>

#include "./Matrix/ATSPMatrix.h"
#include "./Solutions/Utils/GreedyAlgorithm.h"
#include "./Solutions/SimulatedAnnealing.h"
#include "./MeasureTime/Timer.h"

int main() {
    ATSPMatrix *matrix = new ATSPMatrix();
    matrix->loadFromFile("../Resources/br17");
    //matrix->loadFromFile("../Resources/ft53");

    auto result = GreedyAlgorithm::solveGreedyAlgorithm(matrix->getMatrix(), matrix->getSize(), 16);

    SimulatedAnnealing *annealing = new SimulatedAnnealing();

    long long start = Timer::read_QPC();
    annealing->mainFun(matrix, 0.98, 120000);
    long long end = Timer::read_QPC();
    auto elapsed = Timer::getMicroSecondsElapsed(start, end);

    std::cout << "cost: " << annealing->bestCost << std::endl;
    std::cout << "path: ";
    for (const auto &item: annealing->bestPath) {
        std::cout << item << ", ";
    }
    std::cout << std::endl;

    std::cout << "Timer: " << elapsed << " us" << std::endl;
    std::cout << "     : " << elapsed / 1000 << " ms" << std::endl;
    std::cout << "     : " << elapsed / 1000000 << " s" << std::endl;

    std::cout << "greedy : " << annealing->greedyAlgorithmCost << std::endl;

    system("PAUSE");
    return 0;
}


/*
 * cost: 39
 * path: 15, 14, 5, 6, 4, 3, 16, 7, 8, 11, 0, 13, 2, 10, 1, 12, 9, 15,
 *
 * cost: 39
path: 11, 0, 2, 13, 12, 10, 9, 1, 14, 6, 5, 15, 3, 4, 7, 16, 8, 11,

 cost: 39
path: 0, 13, 2, 9, 12, 1, 10, 5, 15, 6, 14, 3, 4, 16, 7, 8, 11, 0,
*/