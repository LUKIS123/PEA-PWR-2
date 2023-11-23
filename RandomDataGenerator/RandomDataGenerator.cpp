#include "RandomDataGenerator.h"


double RandomDataGenerator::generateRandomDouble(int from, int to) {
    std::uniform_real_distribution<double> dist(from, to);
    std::random_device rd;
    std::mt19937 gen(rd());
    return dist(gen);
}

int RandomDataGenerator::generateVertexInRange(int from, int to) {
    std::random_device rdev;
    std::mt19937 gen(rdev());
    std::uniform_int_distribution<> dist(from, to);
    return dist(gen);
}
