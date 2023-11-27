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
    bestPath = currentPath;
    bestCost = greedyAlgorithmCost;

    //startingTemperature = greedyAlgorithmCost * alpha;
    // todo: to najlepsze
    // startingTemperature = greedyAlgorithmCost * matrixSize;
    //singleStepLength = int(greedyAlgorithmCost * alpha);
    //singleStepLength = matrixSize * matrixSize*2;

    // todo: to najlepsze
    //singleStepLength = int(greedyAlgorithmCost * 1.25);
    singleStepLength = matrixSize * matrixSize;

//    currentTemperature = startingTemperature;
    breakTemperature = std::pow(10.0, -9);

    startingTemperature = calculateInitialTemperature(matrix, matrixSize);
    currentTemperature = startingTemperature;
//    singleStepLength = matrixSize * matrixSize * 2;

//    std::cout << "temp1 ; " << startingTemperature;
//    std::cout << "\ntemp2 ; " << greedyAlgorithmCost * matrixSize;
//    return;

    solveTSP();
}

void SimulatedAnnealing::solveTSP() {
    std::chrono::time_point breakAlgoTimePoint = std::chrono::system_clock::now() +
                                                 std::chrono::duration_cast<std::chrono::seconds>(
                                                         std::chrono::duration<int>(timeoutSeconds)
                                                 );
    while (currentTemperature > breakTemperature) {
        for (int step = 0; step < singleStepLength; step++) {
            auto changedPath = perturbPath(currentPath, matrixSize);
            int changedPathCost = calculateCost(matrix, changedPath);
            if (changedPathCost <= currentCost) {
                currentPath = changedPath;
                currentCost = changedPathCost;
                if (changedPathCost <= bestCost) {
                    bestPath = changedPath;
                    bestCost = changedPathCost;
                }
            } else {
                if (acceptanceFunction(currentCost, changedPathCost, currentTemperature)) {
                    currentPath = changedPath;
                    currentCost = changedPathCost;
                }
            }
        }
        // Schladzanie temperatury po petli for
        currentTemperature = CoolingFunctions::updateWithLinearCooling(currentTemperature, coolingFactor);

        // Przerwanie petli po przekroczeniu kryterium stopu
        if ((breakAlgoTimePoint - std::chrono::system_clock::now()).count() < 0) {
            break;
        }

    }
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
    // TODO: do ewentuiualenj poprawy, nie trzeba liczyc calego kosztu sciezki na nowo, wystarczy zmeinic wierzcholki przed i po swapnietym
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

double SimulatedAnnealing::calculateInitialTemperature(int **matrix, int size) {
    int movesCount = 100;
    int steps = matrixSize * 100;
    int totalCostChange = 0;

    for (int i = 0; i < movesCount; i++) {
        auto currentSolution = generateRandomSolution();
        int currentSolCost = currentSolution.second;
        for (int j = 0; j < steps; j++) {
            auto newSolution = perturbPath(currentSolution.first, size);
            int newCost = calculateCost(matrix, newSolution);
            totalCostChange += abs(newCost - currentSolCost);
        }
    }

    double averageCostChange = totalCostChange / (movesCount * steps);
    return -averageCostChange / log(0.85);
}

std::pair<std::vector<int>, int> SimulatedAnnealing::generateRandomSolution() {
    std::vector<int> path(matrixSize);
    std::iota(std::begin(path), std::end(path), 0);
    for (int i = 0; i < matrixSize * matrixSize; i++) {
        int v1 = RandomDataGenerator::generateVertexInRange(0, matrixSize - 1);
        int v2;
        do {
            v2 = RandomDataGenerator::generateVertexInRange(0, matrixSize - 1);
        } while (v2 == v1);
        std::swap(path[v1], path[v2]);
    }
    path.push_back(path[0]);
    int cost = calculateCost(matrix, path);
    return std::make_pair(path, cost);
}

void SimulatedAnnealing::displayLatestResults() {
    std::cout << "Greedy algo cost: " << greedyAlgorithmCost << std::endl;
    std::cout << "SIMULATED ANNEALING RESULTS:" << std::endl;
    std::cout << "Path: ";
    for (const auto &item: bestPath) {
        std::cout << item << ", ";
    }
    std::cout << std::endl;
    std::cout << "SIMULATED ANNEALING Cost: " << bestCost << std::endl;
    std::cout << "END TEMPERATURE: " << currentTemperature << std::endl;
}
