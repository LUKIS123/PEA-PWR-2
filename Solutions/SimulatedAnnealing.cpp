#include "SimulatedAnnealing.h"


void SimulatedAnnealing::clearMemory() {
    if (testing) {
        timestamps.clear();
        solutionProgressionPoints.clear();
    }
    bestCostFoundQPC = Timer::read_QPC();
    currentPath.clear();
    bestPath.clear();
    currentCost = INT_MAX;
    bestCost = INT_MAX;
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
    std::cout << "END TEMPERATURE [Tk]: " << currentTemperature << std::endl;
    std::cout << "exp(-1/Tk): " << exp((-1 / currentTemperature)) << std::endl;
}

// Wyznaczanie wspolczynnikow i uruchomienie algorytmu
void SimulatedAnnealing::mainFun(ATSPMatrix *ATSPMatrix, double alpha, int timeout, long long int startQPC) {
    clearMemory();
    this->startQPC = startQPC;

    this->matrix = ATSPMatrix->getMatrix();
    this->matrixSize = ATSPMatrix->getSize();
    this->coolingFactor = alpha;
    this->timeoutSeconds = timeout;

    auto pathCostPair = GreedyAlgorithm::getBestGreedyAlgorithmResult(matrix, matrixSize);
    if (testing) {
        bestCostFoundQPC = Timer::read_QPC();
        timestamps.push_back(Timer::getMicroSecondsElapsed(startQPC, bestCostFoundQPC) / 1000);
        solutionProgressionPoints.push_back(pathCostPair.second);
    }
    greedyAlgorithmCost = pathCostPair.second;
    currentPath = pathCostPair.first;
    currentCost = greedyAlgorithmCost;
    bestPath = currentPath;
    bestCost = greedyAlgorithmCost;

    startingTemperature = calculateInitialTemperature(matrix, matrixSize);
    currentTemperature = startingTemperature;
    singleStepLength = matrixSize * 10;

    solveTSP();
}

// Funckja zawierajaca glowna petle algorytmu
void SimulatedAnnealing::solveTSP() {
    std::chrono::time_point breakAlgoTimePoint = std::chrono::system_clock::now() +
                                                 std::chrono::duration_cast<std::chrono::seconds>(
                                                         std::chrono::duration<int>(timeoutSeconds)
                                                 );
    while ((breakAlgoTimePoint - std::chrono::system_clock::now()).count() > 0) {
        for (int step = 0; step < singleStepLength; step++) {
            // Wyznaczanie sasiada zamieniajac 2 losowe wierzcholki
            auto changedPath = perturbPath(currentPath, matrixSize);
            int changedPathCost = calculateCost(matrix, changedPath);
            // Akceptowanie nowego rozwiazania jesli nie jest gorsze od aktualnego
            if (changedPathCost <= currentCost) {
                currentPath = changedPath;
                currentCost = changedPathCost;

                // Aktualizowanie najlepszego rozwiazania
                if (changedPathCost < bestCost) {
                    bestPath = changedPath;
                    bestCost = changedPathCost;
                    bestCostFoundQPC = Timer::read_QPC();
                    // Zapis kazdej zmiany na lepsze oraz czasu w ktorej znaleziono rozwiazanie
                    if (testing) {
                        timestamps.push_back(Timer::getMicroSecondsElapsed(startQPC, bestCostFoundQPC) / 1000);
                        solutionProgressionPoints.push_back(bestCost);
                    }
                }

            } else if (acceptanceFunction(currentCost, changedPathCost, currentTemperature)) {
                currentPath = changedPath;
                currentCost = changedPathCost;
            }

        }
        // Schladzanie temperatury po petli for (schodkowe zmniejszanie temperatury)
        currentTemperature = CoolingFunctions::updateWithLinearCooling(currentTemperature, coolingFactor);
    }
}

// Funkcja zwracajaca decyzje o akceptacji badz odrzuceniu rozwiazania na podstawie prawdopodobienstwa wyznaczonego ze wzoru dla algorytmu SW
bool SimulatedAnnealing::acceptanceFunction(int currentVertexWeight, int nextVertexWeight, double temperature) {
    double probability = std::min(1.0, std::exp((double) (-(nextVertexWeight - currentVertexWeight) / temperature)));
    double random = RandomDataGenerator::generateRandomDouble(0, 1);
    if (random < probability) {
        return true;
    } else {
        return false;
    }
}

// Funkcja sluzaca do obliczenia kosztu sciezki (cyklu Hamiltona)
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

// Funckja generujaca nowe rozwiazanie (sasiada) poprzez losowa zamiane 2 wierzcholkow
std::vector<int> SimulatedAnnealing::perturbPath(std::vector<int> path, int size) {
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

// Funckja sluzaca do wyznaczanie poczatkowej temperatury na podstawie sredniego kosztu ruchu w grafie (ruchy wykonywane sa w sposob losowy)
double SimulatedAnnealing::calculateInitialTemperature(int **matrix, int size) {
    int movesCount = 100;
    if (matrixSize > 100) {
        movesCount = matrixSize;
    }
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

    double averageCostChange = (totalCostChange / (movesCount * steps));
    return -averageCostChange / log(0.85);
}

// Funckja pomocnicza dla funkcji wyznaczajacej temperature poczatkowa, sluzaca wygenerowaniu losowej sciezki
std::pair<std::vector<int>, int> SimulatedAnnealing::generateRandomSolution() {
    std::vector<int> path(matrixSize);
    std::iota(std::begin(path), std::end(path), 0);
    for (int i = 0; i < matrixSize * 2; i++) {
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
