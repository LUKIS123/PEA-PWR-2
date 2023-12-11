#include "ATSPMatrix.h"

ATSPMatrix::ATSPMatrix() = default;

ATSPMatrix::~ATSPMatrix() {
    clearData();
}

int **ATSPMatrix::getMatrix() {
    return matrix;
}

int ATSPMatrix::getSize() {
    return size;
}

// Wczytanie macierzy z pliku
void ATSPMatrix::loadFromFile(const std::string &filename) {
    clearData();

    std::ifstream file(filename + ".atsp");
    if (file.good()) {
        std::string data;

        do {
            file >> data;
        } while (data != "DIMENSION:");
        file >> size;

        do {
            file >> data;
        } while (data != "EDGE_WEIGHT_SECTION");

        matrix = new int *[size];
        for (int i = 0; i < size; i++) {
            matrix[i] = new int[size];
        }

        int weight;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file >> weight;
                matrix[i][j] = weight;
            }
        }
        file.close();
        exists = true;
    } else {
        std::cout << "File error - OPEN" << std::endl;
        exists = false;
    }
}

void ATSPMatrix::clearData() {
    if (matrix != nullptr) {
        for (int i = 0; i < size; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

// Wyswietlanie macierzy
void ATSPMatrix::displayMatrix() {
    if (matrix == nullptr) {
        std::cout << "Matrix is empty" << std::endl;
        return;
    }
    std::cout << "\nMatrix: " << "[Size: " << size << "]" << std::endl;
    std::cout << "  ";
    for (int i = 0; i < size; i++) {
        if (i > 10) std::cout << " ";
        else std::cout << "  ";
        std::cout << i;
    }
    std::cout << "\n\n";
    for (int i = 0; i < size; i++) {
        std::cout << i;
        if (i < 10) std::cout << " ";
        for (int j = 0; j < size; j++) {
            std::cout << "  ";
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

// Obliczanie kosztu sciezki
void ATSPMatrix::calculatePathCost(const std::vector<int> &path) {
    if (matrix == nullptr) {
        std::cout << "Matrix is empty" << std::endl;
        return;
    }

    int pathCost = 0;
    auto currentV = path.begin();
    auto nextV = ++path.begin();
    for (; nextV != path.end(); currentV++) {
        pathCost += matrix[*currentV][*nextV];
        nextV++;
    }

    std::cout << "Path:" << std::endl;
    for (const auto &item: path) {
        std::cout << item << ", ";
    }
    std::cout << std::endl;
    std::cout << "CALCULATED COST: " << pathCost << std::endl;
}
