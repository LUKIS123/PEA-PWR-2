#ifndef PEA_PWR_2_GREEDYALGORITHM_H
#define PEA_PWR_2_GREEDYALGORITHM_H

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

class GreedyAlgorithm {
public:
    static std::pair<std::vector<int>, int> solveGreedyAlgorithm(int **matrix, int matrixSize, int startVertex);

    static std::pair<std::vector<int>, int> getBestGreedyAlgorithmResult(int **matrix, int matrixSize);
};


#endif //PEA_PWR_2_GREEDYALGORITHM_H
