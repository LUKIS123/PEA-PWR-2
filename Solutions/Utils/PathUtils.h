#ifndef PEA_PWR_2_PATHUTILS_H
#define PEA_PWR_2_PATHUTILS_H

#include <iostream>
#include <vector>
#include "../../RandomDataGenerator/RandomDataGenerator.h"

class PathUtils {
public:
    static std::pair<std::vector<int>, std::pair<int, int>> swapTwoVertices(std::vector<int> path, int size);

    static int calculateCost(int **matrix, const std::vector<int> &path);

};


#endif //PEA_PWR_2_PATHUTILS_H
