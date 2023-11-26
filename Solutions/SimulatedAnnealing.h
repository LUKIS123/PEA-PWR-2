#ifndef PEA_PWR_2_SIMULATEDANNEALING_H
#define PEA_PWR_2_SIMULATEDANNEALING_H

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <utility>
#include <cmath>
#include <chrono>
#include "../Matrix/ATSPMatrix.h"
#include "./Utils/GreedyAlgorithm.h"
#include "./Utils/CoolingFunctions.h"
#include "../RandomDataGenerator/RandomDataGenerator.h"

class SimulatedAnnealing {
private:
    int **matrix;
    int matrixSize;
    double coolingFactor = 0.99;
    int timeoutSeconds = 120;
    int singleStepLength;

public:
    int greedyAlgorithmCost;

    std::vector<int> currentPath;
    int currentCost = INT_MAX;

    std::vector<int> bestPath;
    int bestCost = INT_MAX;

    double startingTemperature;
    double currentTemperature;
    double breakTemperature;

    static bool acceptanceFunction(int currentVertexWeight, int nextVertexWeight, double temperature);

    void mainFun(ATSPMatrix *ATSPMatrix, double alpha, int timeout);

    void solveTSP();

    static int calculateCost(int **matrix, const std::vector<int> &path);

    static std::vector<int> perturbPath(std::vector<int> path, int size);

    double calculateInitialTemperature(int **matrix, int size);

    std::pair<std::vector<int>, int> generateRandomSolution();

    void displayLatestResults();
};


#endif //PEA_PWR_2_SIMULATEDANNEALING_H
