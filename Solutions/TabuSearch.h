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
#include "../Matrix/ATSPMatrix.h"
#include "./Utils/GreedyAlgorithm.h"
#include "../RandomDataGenerator/RandomDataGenerator.h"
#include "../MeasureTime/Timer.h"


class TabuSearch {
private:
    int **matrix = nullptr;
    int matrixSize;
    int timeoutSeconds = 120;

    int tabuIterationsCadence;
    int **tabuMoves = nullptr;
    int diversificationEventCounter = 0;
    int diversificationEventIterations = INT_MAX;

    int masterListValidity = 10;
    std::list<std::pair<std::pair<int, int>, int>> neighboursMasterList;
    int lastMasterListElementCost;

    class comp {
    public:
        bool
        operator()(const std::pair<std::pair<int, int>, int> &a, const std::pair<std::pair<int, int>, int> &b) {
            return a.second < b.second;
        }
    };

public:
    bool testing = false;
    std::vector<double> timestamps;
    long long int startQPC;

    int greedyAlgorithmCost;

    std::vector<int> currentPath;
    int currentCost = INT_MAX;

    std::vector<int> currentBestPath;
    int currentBestCost = INT_MAX;

    long long int bestCostFoundQPC;
    std::vector<int> bestSolutionFirstOccurrence;
    int bestSolutionFirstOccurrenceCost = INT_MAX;

    virtual ~TabuSearch();

    void mainFun(ATSPMatrix *ATSPMatrix, int timeout, long long int startQPC);

    void solveTSP();

    void displayLatestResults();

    std::vector<std::pair<std::pair<int, int>, int>>
    getNextMovesFromNeighbours(const std::vector<int> &solution);

    int getSwappedPathCost(int v1, int v2, std::vector<int> path);

    std::list<std::pair<std::pair<int, int>, int>>
    filterTabuSwaps(const std::vector<std::pair<std::pair<int, int>, int>> &allNeighbours);

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
