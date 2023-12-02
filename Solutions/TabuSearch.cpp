#include "TabuSearch.h"

TabuSearch::~TabuSearch() {
    if (tabuMoves != nullptr) {
        for (int i = 0; i < matrixSize; i++) {
            delete[] tabuMoves[i];
        }
        delete[] tabuMoves;
        tabuMoves = nullptr;
    }
}

void TabuSearch::clearMemory() {
    neighboursMasterList.clear();
    currentPath.clear();
    bestPath.clear();
    currentCost = INT_MAX;
    bestCost = INT_MAX;
    diversificationEventCounter = 0;
    if (tabuMoves != nullptr) {
        for (int i = 0; i < matrixSize; i++) {
            delete[] tabuMoves[i];
        }
        delete[] tabuMoves;
    }
}

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

void TabuSearch::mainFun(ATSPMatrix *ATSPMatrix, int timeout) {
    clearMemory();

    this->matrix = ATSPMatrix->getMatrix();
    this->matrixSize = ATSPMatrix->getSize();
    this->tabuIterationsCadence = (int) sqrt(matrixSize) * 5;
    this->timeoutSeconds = timeout;

    auto pathCostPair = GreedyAlgorithm::getBestGreedyAlgorithmResult(matrix, matrixSize);
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

    if (matrixSize > 200) {
        masterListValidity = (int) (matrixSize * 0.04);
    } else {
        masterListValidity = 7;
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

    while ((breakAlgoTimePoint - std::chrono::system_clock::now()).count() > 0) {
        // Przegladanie sasiednich rozwiazan (wszystkie mozliwe zamiany dwoch wierzcholkow),
        // tworznie master listy zawierajacej n elementow, aktualizowana co jakis czas
        if (neighboursMasterList.empty()) {
            neighboursMasterList = getNextMovesFromNeighboursMasterList(currentPath);
        } else {
            updateMasterListCosts(neighboursMasterList, currentPath);
        }

        std::pair<int, int> nextVertexPair = neighboursMasterList.front().first;
        int nextVertexPairSwapCost = neighboursMasterList.front().second;

        currentPath.pop_back();
        swapVectorElements(nextVertexPair.first, nextVertexPair.second, currentPath);
        currentPath.push_back(currentPath[0]);
        currentCost = nextVertexPairSwapCost;

        // Aktualizacja licznika uruchomienia strategii dywersyfikacji
        if (currentCost >= bestCost) {
            ++iterationsWithoutImprovement;
        } else {
            iterationsWithoutImprovement = 0;
        }
        // Aktualizacja najlepszego rozwiazania
        if (currentCost <= bestCost) {
            bestPath = currentPath;
            bestCost = currentCost;
            bestCostFoundQPC = Timer::read_QPC();
        }

        // Aktualizacja listy tabu
        updateTabuList(nextVertexPair.first, nextVertexPair.second);

        // Aktualizacja master listy sasiadow
        neighboursMasterList.pop_front();

        // Dywersyfikacja -> jesli przekroczono okreslona ilosc iteracji bez lepszego rozwiazania
        if (iterationsWithoutImprovement >= tabuIterationsCadence * 2) {
            auto bestDiversificationCandidate = generateDiversificationCandidate();
            currentPath = bestDiversificationCandidate.first;
            currentCost = bestDiversificationCandidate.second;
            if (currentCost <= bestCost) {
                bestPath = currentPath;
                bestCost = currentCost;
                bestCostFoundQPC = Timer::read_QPC();
            }

            iterationsWithoutImprovement = 0;
            ++diversificationEventCounter;

            if (diversificationEventCounter % 2 == 0) {
                neighboursMasterList = getNextMovesFromNeighboursMasterList(currentPath);
            }

        }

        iteration++;
    }
}

std::vector<std::pair<std::pair<int, int>, int>>
TabuSearch::getNextMovesFromNeighbours(const std::vector<int> &solution) {
    auto neighbourList = std::vector<std::pair<std::pair<int, int>, int>>();
    neighbourList.reserve((matrixSize * matrixSize) / 2);
    for (int i = 0; i < matrixSize - 1; i++) {
        for (int j = i + 1; j < matrixSize; j++) {
            int cost = getSwappedPathCost(i, j, solution);
            neighbourList.emplace_back(std::make_pair(i, j), cost);
        }
    }
    std::sort(neighbourList.begin(), neighbourList.end(), comp());
    return neighbourList;
}

int TabuSearch::getSwappedPathCost(int v1, int v2, std::vector<int> path) {
    path.pop_back();
    swapVectorElements(v1, v2, path);
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
TabuSearch::filterTabuSwaps(const std::vector<std::pair<std::pair<int, int>, int>> &allNeighbours) {
    std::list<std::pair<std::pair<int, int>, int>> filtered;
    for (const auto &item: allNeighbours) {
        if (tabuMoves[item.first.first][item.first.second] == 0) {
            filtered.push_back(item);
        }
    }
    return filtered;
}

// Funkcja aktualizujaca liste tabu po kazdej iteracji
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
    std::cout << "Current: " << currentCost << ", Best: " << bestCost << std::endl;

    int candidateCost = INT_MAX;
    std::vector<int> candidatePath;

    if (diversificationEventCounter % 2 == 0) {
        int v1 = RandomDataGenerator::generateVertexInRange(0, matrixSize - 1);
        int v2;
        do {
            v2 = RandomDataGenerator::generateVertexInRange(0, matrixSize - 1);
        } while (v2 == v1 || abs((v1 - v2)) == 1);
        if (v1 > v2) {
            std::swap(v1, v2);
        }

        candidatePath = bestPath;
        candidatePath.pop_back();

        std::random_device rdev;
        std::mt19937 gen(rdev());
        std::shuffle(candidatePath.begin() + v1, candidatePath.begin() + v2, gen);

        candidatePath.push_back(candidatePath[0]);
    } else {
        std::vector<int> tmp;

        for (int i = 0; i < matrixSize; i++) {
            for (int j = i + 1; j < matrixSize; j++) {
                tmp = bestPath;
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

                if (tmpCost < candidateCost) {
                    candidatePath = tmp;
                    candidateCost = tmpCost;
                    if (candidateCost < bestCost) {
                        break;
                    }
                }
            }
        }
    }

    candidateCost = calculatePathCost(matrix, candidatePath);
    return std::make_pair(candidatePath, candidateCost);
}

int TabuSearch::calculatePathCost(int **matrix, const std::vector<int> &path) {
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
TabuSearch::getNextMovesFromNeighboursMasterList(const std::vector<int> &solution) {
    auto allNeighboursSorted = getNextMovesFromNeighbours(solution);
    auto nonTabuNeighbours = filterTabuSwaps(allNeighboursSorted);

    if (nonTabuNeighbours.empty()) {
        std::copy(allNeighboursSorted.begin(), allNeighboursSorted.end(), std::back_inserter(nonTabuNeighbours));
    }

    auto end = std::next(nonTabuNeighbours.begin(), std::min(masterListValidity, (int) nonTabuNeighbours.size()));
    std::list<std::pair<std::pair<int, int>, int>> masterList(nonTabuNeighbours.begin(), end);

    auto bestNeighbour = allNeighboursSorted.front();
    if (tabuMoves[bestNeighbour.first.first][bestNeighbour.first.second] != 0 && bestCost > bestNeighbour.second) {
        masterList.push_front(bestNeighbour);
    }

    return masterList;
}

void
TabuSearch::updateMasterListCosts(std::list<std::pair<std::pair<int, int>, int>> &masterList, std::vector<int> &path) {
    for (auto &item: masterList) {
        item.second = getSwappedPathCost(item.first.first, item.first.second, path);
    }
}

void TabuSearch::swapVectorElements(int v1, int v2, std::vector<int> &path) const {
    int index1 = INT_MIN, index2 = INT_MIN;
    for (int i = 0; i < matrixSize; ++i) {
        if (path[i] == v1) {
            index1 = i;
        } else if (path[i] == v2) {
            index2 = i;
        }

        if (index1 != INT_MIN && index2 != INT_MIN) {
            break;
        }
    }
    std::swap(path[index1], path[index2]);
}
