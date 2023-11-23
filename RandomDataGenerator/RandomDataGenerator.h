#ifndef PEA_PWR_2_RANDOMDATAGENERATOR_H
#define PEA_PWR_2_RANDOMDATAGENERATOR_H

#include <iostream>
#include <random>

class RandomDataGenerator {
public:
    static double generateRandomDouble(int from, int to);

    static int generateVertexInRange(int from, int to);
};


#endif //PEA_PWR_2_RANDOMDATAGENERATOR_H
