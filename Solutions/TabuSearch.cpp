#include "TabuSearch.h"

void TabuSearch::displayLatestResults() {
}

void TabuSearch::mainFun(ATSPMatrix *ATSPMatrix, int tabuIterationsCount, int iterations, int timeout) {
    this->matrix = ATSPMatrix->getMatrix();
    this->matrixSize = ATSPMatrix->getSize();
    this->tabuIterations = tabuIterationsCount;
    this->maxIterations = iterations;
    this->timeoutSeconds = timeout;

    int startingVertex = RandomDataGenerator::generateVertexInRange(0, matrixSize - 1);
    auto pathCostPair = GreedyAlgorithm::solveGreedyAlgorithm(matrix, matrixSize, startingVertex);
    greedyAlgorithmCost = pathCostPair.second;
    currentPath = pathCostPair.first;
    currentCost = greedyAlgorithmCost;
    bestPath = currentPath;
    bestCost = currentCost;

    tabuMoves = new int *[matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        tabuMoves[i] = new int[matrixSize];
    }
    int currentFillCount = 1;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (j < currentFillCount) {
                tabuMoves[i][j] = INT_MAX;
            } else {
                tabuMoves[i][j] = 0;
            }
        }
        currentFillCount += 1;
    }

    solveTSP();
}

void TabuSearch::solveTSP() {
    std::chrono::time_point breakAlgoTimePoint = std::chrono::system_clock::now() +
                                                 std::chrono::duration_cast<std::chrono::seconds>(
                                                         std::chrono::duration<int>(timeoutSeconds)
                                                 );

    int iteration = 0;
    while (iteration < maxIterations && (breakAlgoTimePoint - std::chrono::system_clock::now()).count() < 0) {
        auto neighborSolutions= getNextMoves(currentPath);



        iteration++;
    }
}

std::list<std::pair<std::pair<int, int>, int>> TabuSearch::getNextMoves(std::vector<int> solution) {
    solution.pop_back();
    std::list<std::pair<std::pair<int, int>, int>> swapsCostList;
    for (int i = 0; i < matrixSize - 1; i++) {
        for (int j = i + 1; j < matrixSize; j++) {
            int cost = getSwappedPathCost(i, j, solution);
            swapsCostList.emplace_back(std::make_pair(i, j), cost);
        }
    }
    swapsCostList.sort([](auto const &a, auto const &b) {
        return a.second < b.second;
    });
    return swapsCostList;
}

int TabuSearch::getSwappedPathCost(int v1, int v2, std::vector<int> path) {
    path.pop_back();
    std::swap(path[v1], path[v2]);
    path.push_back(path[0]);

    auto currentV = path.begin();
    auto nextV = ++path.begin();
    int newCost = 0;
    for (; nextV != path.end(); currentV++) {
        newCost += matrix[*currentV][*nextV];
        nextV++;
    }
    return newCost;
}




