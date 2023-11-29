#ifndef PEA_PWR_2_TABUSEARCH_H
#define PEA_PWR_2_TABUSEARCH_H

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <utility>
#include <cmath>
#include <chrono>
#include "../Matrix/ATSPMatrix.h"
#include "./Utils/GreedyAlgorithm.h"
#include "../RandomDataGenerator/RandomDataGenerator.h"


class TabuSearch {
private:
    int **matrix;
    int matrixSize;
    int timeoutSeconds = 120;

    int maxIterations;
    int tabuIterationsCadence;
    int **tabuMoves;

public:
    int greedyAlgorithmCost;

    std::vector<int> currentPath;
    int currentCost = INT_MAX;

    std::vector<int> bestPath;
    int bestCost = INT_MAX;

    std::list<int> *latestCostsList;

    void mainFun(ATSPMatrix *ATSPMatrix, int tabuCadenceIterationsCount, int iterations, int timeout);

    void solveTSP();

    void displayLatestResults();

    std::list<std::pair<std::pair<int, int>, int>> getNextMoves(std::vector<int> solution);

    int getSwappedPathCost(int v1, int v2, std::vector<int> path);

    std::list<std::pair<std::pair<int, int>, int>>
    filterTabuSwaps(const std::list<std::pair<std::pair<int, int>, int>> &swaps);

    void updateTabuList(int v1, int v2);

    std::pair<std::vector<int>, int> generateDiversificationCandidate();

};


#endif //PEA_PWR_2_TABUSEARCH_H
