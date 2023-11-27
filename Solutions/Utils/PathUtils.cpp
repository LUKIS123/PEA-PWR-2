#include "PathUtils.h"

std::pair<std::vector<int>, std::pair<int, int>> PathUtils::swapTwoVertices(std::vector<int> path, int size) {
    // TODO: do ewentuiualenj poprawy, nie trzeba liczyc calego kosztu sciezki na nowo, wystarczy zmeinic wierzcholki przed i po swapnietym
    path.pop_back();
    int v1 = RandomDataGenerator::generateVertexInRange(0, size - 1);
    int v2;
    do {
        v2 = RandomDataGenerator::generateVertexInRange(0, size - 1);
    } while (v2 == v1);

    std::swap(path[v1], path[v2]);
    path.push_back(path[0]);
    return std::make_pair(path, std::make_pair(v1, v2));
}

int PathUtils::calculateCost(int **matrix, const std::vector<int> &path) {
    auto currentV = path.begin();
    auto nextV = ++path.begin();
    int newCost = 0;

    for (; nextV != path.end(); currentV++) {
        newCost += matrix[*currentV][*nextV];
        nextV++;
    }
    return newCost;
}
