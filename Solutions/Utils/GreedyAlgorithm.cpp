#include "GreedyAlgorithm.h"

// UWAGA: Dla algorytmu zachlannego wybor wierzcholka startowego ma znaczenie!!!
std::pair<std::vector<int>, int> GreedyAlgorithm::solveGreedyAlgorithm(int **matrix, int matrixSize, int start) {
    int startVertex = start;
    int distance = 0;

    bool *visited = new bool[matrixSize];
    std::fill(visited, visited + matrixSize, false);

    std::vector<int> path;
    int currentIndex = startVertex;

    do {
        visited[currentIndex] = true;
        path.push_back(currentIndex);
        int min = INT_MAX;

        int nextVertex;
        for (int column = 0; column < matrixSize; column++) {
            if (visited[column] || currentIndex == column) {
                continue;
            }
            if (min > matrix[currentIndex][column]) {
                min = matrix[currentIndex][column];
                nextVertex = column;
            }
        }
        distance += min;
        currentIndex = nextVertex;
    } while (path.size() != (matrixSize - 1));

    path.push_back(currentIndex);
    path.push_back(startVertex);
    distance += matrix[currentIndex][startVertex];

    return std::make_pair(path, distance);
}

// Funkcja wykonujaca algorytm zachlanny sprawdzajac wszystkie wierzcholki i zwracajaca najlepszy rezultat
std::pair<std::vector<int>, int> GreedyAlgorithm::getBestGreedyAlgorithmResult(int **matrix, int matrixSize) {
    int bestCost = INT_MAX;
    std::vector<int> bestPath;

    for (int i = 0; i < matrixSize; i++) {
        auto solution = solveGreedyAlgorithm(matrix, matrixSize, i);
        if (solution.second < bestCost) {
            bestPath = solution.first;
            bestCost = solution.second;
        }
    }
    return std::make_pair(bestPath, bestCost);
}
