#include "SimulatedAnnealing.h"


void SimulatedAnnealing::mainFun(ATSPMatrix *ATSPMatrix, double alpha, int timeout) {
    this->matrix = ATSPMatrix->getMatrix();
    this->matrixSize = ATSPMatrix->getSize();
    this->coolingFactor = alpha;
    this->timeoutSeconds = timeout;

    int startingVertex = RandomDataGenerator::generateVertexInRange(0, matrixSize - 1);
    auto pathCostPair = GreedyAlgorithm::solveGreedyAlgorithm(matrix, matrixSize, startingVertex);
    greedyAlgorithmCost = pathCostPair.second;
    currentPath = pathCostPair.first;
    currentCost = greedyAlgorithmCost;

    //startingTemperature = greedyAlgorithmCost * alpha;
    startingTemperature = greedyAlgorithmCost * matrixSize;
    singleStepLength = int(greedyAlgorithmCost * alpha);

    currentTemperature = startingTemperature;
    breakTemperature = std::pow(10.0, -9);

    solveTSP();
}

void SimulatedAnnealing::solveTSP() {
    while (currentTemperature > breakTemperature) {
        for (int step = 0; step < singleStepLength; step++) {
            auto changedPath = perturbPath(currentPath, matrixSize);
            int changedPathCost = calculateCost(matrix, changedPath);
            if (changedPathCost <= currentCost) {
                currentPath = changedPath;
                currentCost = changedPathCost;
            } else {
                if (acceptanceFunction(currentCost, changedPathCost, currentTemperature)) {
                    currentPath = changedPath;
                    currentCost = changedPathCost;
                }
            }
        }
//        std::cout << "temp " << currentTemperature << std::endl;
        currentTemperature = CoolingFunctions::updateWithLinearCooling(currentTemperature, coolingFactor);
    }

    bestPath = currentPath;
    bestCost = currentCost;
}

bool SimulatedAnnealing::acceptanceFunction(int currentVertexWeight, int nextVertexWeight, double temperature) {
    double probability = std::min(1.0, std::exp((double) (-(nextVertexWeight - currentVertexWeight) / temperature)));
    double random = RandomDataGenerator::generateRandomDouble(0, 1);
    if (random < probability) {
        return true;
    } else {
        return false;
    }
}

int SimulatedAnnealing::calculateCost(int **matrix, const std::vector<int> &path) {
    auto currentV = path.begin();
    auto nextV = ++path.begin();
    int newCost = 0;

    for (; nextV != path.end(); currentV++) {
        newCost += matrix[*currentV][*nextV];
        nextV++;
    }
    return newCost;
}

std::vector<int> SimulatedAnnealing::perturbPath(std::vector<int> path, int size) {
    // todo : last_popback i potem zerowy indeks na koniec skopiowac bo inaczej sie pierdoli
    path.pop_back();
    int v1 = RandomDataGenerator::generateVertexInRange(0, size - 1);
    int v2;
    do {
        v2 = RandomDataGenerator::generateVertexInRange(0, size - 1);
    } while (v2 == v1);

    std::swap(path[v1], path[v2]);
    path.push_back(path[0]);
    return path;
}
