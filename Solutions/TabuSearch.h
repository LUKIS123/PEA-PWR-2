#ifndef PEA_PWR_2_TABUSEARCH_H
#define PEA_PWR_2_TABUSEARCH_H

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <utility>
#include <cmath>
#include <chrono>
#include <random>
#include <queue>
#include "../Matrix/ATSPMatrix.h"
#include "./Utils/GreedyAlgorithm.h"
#include "../RandomDataGenerator/RandomDataGenerator.h"
#include "../MeasureTime/Timer.h"


class TabuSearch {
private:
    int **matrix = nullptr;
    int matrixSize;
    int timeoutSeconds = 120;

    int maxIterations = 1000000000;
    int tabuIterationsCadence;
    int **tabuMoves = nullptr;

    int masterListValidity = 10;
    std::list<std::pair<std::pair<int, int>, int>> neighboursMasterList;

    class comp {
    public:
        bool
        operator()(std::pair<std::pair<int, int>, int> const &a, std::pair<std::pair<int, int>, int> const &b) const {
            return a.second < b.second;
        }
    };

    std::priority_queue<std::pair<std::pair<int, int>, int>, std::vector<std::pair<std::pair<int, int>, int>>, comp> neighboursPQ;

public:
    int greedyAlgorithmCost;

    std::vector<int> currentPath;
    int currentCost = INT_MAX;

    std::vector<int> bestPath;
    int bestCost = INT_MAX;
    long long int bestCostFoundQPC;

    virtual ~TabuSearch();

    void mainFun(ATSPMatrix *ATSPMatrix, int timeout);

    void solveTSP();

    void displayLatestResults();

    std::vector<std::pair<std::pair<int, int>, int>>
    getNextMovesFromNeighbours(const std::vector<int> &solution);

    int getSwappedPathCost(int v1, int v2, std::vector<int> path);

    std::vector<std::pair<std::pair<int, int>, int>>
    filterTabuSwaps(std::vector<std::pair<std::pair<int, int>, int>> path);

    void updateTabuList(int v1, int v2);

    std::pair<std::vector<int>, int> generateDiversificationCandidate();

    static int calculatePathCost(int **matrix, const std::vector<int> &path);

    std::list<std::pair<std::pair<int, int>, int>>
    getNextMovesFromNeighboursMasterList(const std::vector<int> &solution);

    void updateMasterListCosts(std::list<std::pair<std::pair<int, int>, int>> &masterList, std::vector<int> &path);

    void swapVectorElements(int v1, int v2, std::vector<int> &path) const;

private:
    void clearMemory();
};


#endif //PEA_PWR_2_TABUSEARCH_H
