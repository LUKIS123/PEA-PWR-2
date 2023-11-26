#include "TabuSearch.h"

void TabuSearch::displayLatestResults() {
}

void TabuSearch::mainFun(ATSPMatrix *ATSPMatrix, int tabuListSize, int timeout) {

    this->matrix = ATSPMatrix->getMatrix();
    this->matrixSize = ATSPMatrix->getSize();
    this->tabuListSize = tabuListSize;
    this->timeoutSeconds = timeout;

    int startingVertex = RandomDataGenerator::generateVertexInRange(0, matrixSize - 1);
    auto pathCostPair = GreedyAlgorithm::solveGreedyAlgorithm(matrix, matrixSize, startingVertex);
    greedyAlgorithmCost = pathCostPair.second;
    currentBestPath = pathCostPair.first;
    currentBestCost = greedyAlgorithmCost;

}

void TabuSearch::solveTSP() {

}
