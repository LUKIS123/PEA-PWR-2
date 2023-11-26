#ifndef PEA_PWR_2_TABUSEARCH_H
#define PEA_PWR_2_TABUSEARCH_H

#include "../Matrix/ATSPMatrix.h"
#include "./Utils/GreedyAlgorithm.h"
#include "../RandomDataGenerator/RandomDataGenerator.h"

class TabuSearch {
private:
    int **matrix;
    int matrixSize;
    int tabuListSize;
    int timeoutSeconds = 120;

public:
    int greedyAlgorithmCost;

    std::vector<int> currentBestPath;
    int currentBestCost = INT_MAX;

    void mainFun(ATSPMatrix *ATSPMatrix, int tabuListSize, int timeout);

    void solveTSP();

    void displayLatestResults();

};


#endif //PEA_PWR_2_TABUSEARCH_H
