#include "TabuSearch.h"

void TabuSearch::displayLatestResults() {
    std::cout << "Greedy algo cost: " << greedyAlgorithmCost << std::endl;
    std::cout << "TABU SEARCH RESULTS:" << std::endl;
    std::cout << "Path: ";
    for (const auto &item: bestPath) {
        std::cout << item << ", ";
    }
    std::cout << std::endl;
    std::cout << "TABU SEARCH Cost: " << bestCost << std::endl;
}

// TODO: dodac strategie dywersyfikacji: https://cs.pwr.edu.pl/zielinski/lectures/om/localsearch.pdf
// str 34
// chat gpt oraz zobaczyc co w filmiku na yt (politechn poznan)
void TabuSearch::mainFun(ATSPMatrix *ATSPMatrix, int tabuCadenceIterationsCount, int iterations, int timeout) {
    this->matrix = ATSPMatrix->getMatrix();
    this->matrixSize = ATSPMatrix->getSize();
    this->tabuIterationsCadence = tabuCadenceIterationsCount;
    this->maxIterations = iterations;
    this->timeoutSeconds = timeout;

    int startingVertex = RandomDataGenerator::generateVertexInRange(0, matrixSize - 1);
    auto pathCostPair = GreedyAlgorithm::solveGreedyAlgorithm(matrix, matrixSize, startingVertex);
    greedyAlgorithmCost = pathCostPair.second;
    currentPath = pathCostPair.first;
    currentCost = greedyAlgorithmCost;
    bestPath = currentPath;
    bestCost = currentCost;

    latestCostsList = new std::list<int>(tabuIterationsCadence, INT_MAX);

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
    int iterationsWithoutImprovement = 0;

    while (iteration < maxIterations && (breakAlgoTimePoint - std::chrono::system_clock::now()).count() > 0) {
        auto neighborSolutions = getNextMoves(currentPath);
        auto nonTabuNeighbours = filterTabuSwaps(neighborSolutions);

        if (nonTabuNeighbours.empty()) {
            nonTabuNeighbours = neighborSolutions;
        }

        std::pair<int, int> bestVertexPair = nonTabuNeighbours.front().first;
        int bestVertexPairSwapCost = nonTabuNeighbours.front().second;

        if (bestVertexPairSwapCost > neighborSolutions.front().second) {
            // TODO: nowa wartosc, akceptujemy ruch tabu -> yt 19:00
            bool found =
                    std::find(latestCostsList->begin(), latestCostsList->end(), neighborSolutions.front().second) !=
                    latestCostsList->end();
            if (!found) {
                bestVertexPair = neighborSolutions.front().first;
                bestVertexPairSwapCost = neighborSolutions.front().second;
            }
        }

        std::vector<int> nextSolution = currentPath;
        nextSolution.pop_back();
        std::swap(nextSolution[bestVertexPair.first],
                  nextSolution[bestVertexPair.second]
        );
        nextSolution.push_back(nextSolution[0]);

        currentPath = nextSolution;
        currentCost = bestVertexPairSwapCost;

        if (currentCost < bestCost) {
            iterationsWithoutImprovement++;
        } else {
            iterationsWithoutImprovement = 0;
        }

        if (currentCost <= bestCost) {
            bestPath = currentPath;
            bestCost = currentCost;
        }
        updateTabuList(bestVertexPair.first, bestVertexPair.second);
        latestCostsList->pop_back();
        latestCostsList->push_front(bestVertexPairSwapCost);

        if (iterationsWithoutImprovement >= tabuIterationsCadence) {
            // todo: dywersyfikacja, moze zeby zwiekszyc losowosc dodac warunek iles procent szans na zmiane
            auto bestDiversificationCandidate = generateDiversificationCandidate();
            currentPath = bestDiversificationCandidate.first;
            currentCost = bestDiversificationCandidate.second;
            if (currentCost <= bestCost) {
                bestPath = currentPath;
                bestCost = currentCost;
            }
            iterationsWithoutImprovement = 0;
        }

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

std::list<std::pair<std::pair<int, int>, int>>
TabuSearch::filterTabuSwaps(const std::list<std::pair<std::pair<int, int>, int>> &swaps) {
    std::list<std::pair<std::pair<int, int>, int>> swapsFiltered;
    for (const auto &item: swaps) {
        if (tabuMoves[item.first.first][item.first.second] == 0) {
            swapsFiltered.push_back(item);
        }
    }
    return swapsFiltered;
}

void TabuSearch::updateTabuList(int v1, int v2) {
    for (int i = 0; i < matrixSize - 1; i++) {
        for (int j = i + 1; j < matrixSize; j++) {
            if (tabuMoves[i][j] != 0) {
                tabuMoves[i][j] -= 1;
            }
        }
    }
    tabuMoves[v1][v2] = tabuIterationsCadence;
}

std::pair<std::vector<int>, int> TabuSearch::generateDiversificationCandidate() {
    int bestCandidateCost = INT_MAX;
    std::vector<int> bestCandidate;
    std::vector<int> tmp;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = i + 1; j < matrixSize; j++) {
            tmp = currentPath;
            tmp.pop_back();
            std::reverse(tmp.begin() + i, tmp.begin() + j);
            tmp.push_back(tmp.front());

            auto currentV = tmp.begin();
            auto nextV = ++tmp.begin();
            int tmpCost = 0;
            for (; nextV != tmp.end(); currentV++) {
                tmpCost += matrix[*currentV][*nextV];
                nextV++;
            }

            if (tmpCost < bestCandidateCost) {
                bestCandidate = tmp;
                bestCandidateCost = tmpCost;
            }
        }
    }

    return std::make_pair(bestCandidate, bestCandidateCost);
}
